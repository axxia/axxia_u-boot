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
#include "../common/ncp_nca_reg_defines.h"

#define WFC_TIMEOUT (400000)

#define LOCK_DOMAIN 0

#ifdef ARM64
#define POINTER(address) ((unsigned long *)((unsigned long long)(address)))
#else
#define POINTER(address) ((unsigned long *)((unsigned long)(address)))
#endif

static int ncr_sysmem_mode_disabled = 1;
static int ncr_tracer_disabled = 1;
void ncr_tracer_enable( void ) { ncr_tracer_disabled = 0; }
void ncr_tracer_disable( void ) { ncr_tracer_disabled = 1; }
int ncr_tracer_is_enabled( void ) { return 0 == ncr_tracer_disabled ? 1 : 0; }
void ncr_sysmem_init_mode_enable(void) { ncr_sysmem_mode_disabled = 0; }
void ncr_sysmem_init_mode_disable(void) { ncr_sysmem_mode_disabled = 1; }

static __inline__ ncp_uint32_t ncr_register_read(unsigned long *);
static __inline__ void ncr_register_write(const unsigned, unsigned long *);

static int
ncr_fail(const char *file, const char *function, const int line)
{
	if (1 == ncr_sysmem_mode_disabled)
		return -1;
	
	printf("Config Ring Access Failed: 0x%08lx 0x%08lx\n",
	       (unsigned long)ncr_register_read(POINTER(NCA + NCP_NCA_CFG_RING_ERROR_STAT_R0)),
	       (unsigned long)ncr_register_read(POINTER(NCA + NCP_NCA_CFG_RING_ERROR_STAT_R1)));
	acp_failure(file, function, line);

	return -1;
}

#ifdef NCR_TRACER
static int short_read_count = 100;	/* Make sure this isn't in bss. */

void
ncr_trace_read8(ncp_uint32_t region, ncp_uint32_t offset)
{
	if (100 == short_read_count)
		short_read_count = 0;

	if (0 == short_read_count) {
		++short_read_count;
		printf("ncpRead   -w8 0.%u.%u.0x00%08x",
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
ncr_trace_read16(ncp_uint32_t region, ncp_uint32_t offset)
{
	printf("ncpRead    0.%u.%u.0x00%08x 1\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

	return;
}

void
ncr_trace_read32(ncp_uint32_t region, ncp_uint32_t offset)
{
	printf("ncpRead    0.%u.%u.0x00%08x 1\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset);

	return;
}

static int short_write_count = 100;	/* Make sure this isn't in bss. */

void
ncr_trace_write8(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	if (100 == short_write_count)
		short_write_count = 0;

	if (0 == short_write_count) {
		++short_write_count;
		printf("ncpWrite  -w8 0.%u.%u.0x00%08x 0x%02x",
		       NCP_NODE_ID(region), NCP_TARGET_ID(region),
		       offset, value);
	} else {
		++ short_write_count;
		printf(" 0x%02x", value);

		if (4 == short_write_count) {
			printf("\n");
			short_write_count = 0;
		}
	}

	return;
}

void
ncr_trace_write16(ncp_uint32_t region,
		  ncp_uint32_t offset, ncp_uint32_t value)
{
	printf("ncpWrite   0.%u.%u.0x00%08x 0x%04x\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, value);

	return;
}

void
ncr_trace_write32(ncp_uint32_t region,
		  ncp_uint32_t offset, ncp_uint32_t value)
{
	printf("ncpWrite   0.%u.%u.0x00%08x 0x%08x\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, value);

	return;
}

void
ncr_trace_modify(ncp_uint32_t region,
		 ncp_uint32_t offset, ncp_uint32_t mask, ncp_uint32_t value)
{
	printf("ncpModify  0.%u.%u.0x00%08x 0x%08x 0x%08x\n",
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, mask, value);

	return;
}

void
ncr_trace_poll(ncp_uint32_t region,
	       ncp_uint32_t loops, ncp_uint32_t delay,
	       ncp_uint32_t offset, ncp_uint32_t mask, ncp_uint32_t value)
{
	printf("ncpPoll -l %u -t %u  0.%u.%u.0x00%08x " \
	       "0x%08x 0x%08x\n",
	       loops, delay,
	       NCP_NODE_ID(region), NCP_TARGET_ID(region), offset, mask, value);

	return;
}

#define NCR_TRACE_READ8(region, offset) do {			\
		if (ncr_tracer_is_enabled()) {			\
			ncr_trace_read8(region, offset); }	\
	} while (0);
#define NCR_TRACE_READ16(region, offset) do {			\
		if (ncr_tracer_is_enabled()) {			\
			ncr_trace_read16(region, offset); }	\
	} while (0);
#define NCR_TRACE_READ32(region, offset) do {			\
		if (ncr_tracer_is_enabled()) {			\
			ncr_trace_read32(region, offset); }	\
	} while (0);
#define NCR_TRACE_WRITE8(region, offset, value) do {			\
		if (ncr_tracer_is_enabled()) {				\
			ncr_trace_write8(region, offset, value); }	\
	} while (0);
#define NCR_TRACE_WRITE16(region, offset, value) do {			\
		if (ncr_tracer_is_enabled()) {				\
			ncr_trace_write16(region, offset, value); }	\
	} while (0);
#define NCR_TRACE_WRITE32(region, offset, value) do {			\
		if (ncr_tracer_is_enabled()) {				\
			ncr_trace_write32(region, offset, value); }	\
	} while (0);
#define NCR_TRACE_MODIFY(region, offset, mask, value) do {		\
		if (ncr_tracer_is_enabled()) {				\
			ncr_trace_modify(region, offset, mask, value); } \
	} while (0);
#define NCR_TRACE_POLL(region, loops, delay, offset, mask, value) do {	\
		if (ncr_tracer_is_enabled()) {				\
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
	ncp_uint32_t raw;
	struct {
#ifndef NCP_BIG_ENDIAN
		ncp_uint32_t dbs                 : 16;
		ncp_uint32_t cmd_type            : 4;
		ncp_uint32_t cfg_cmpl_int_enable : 1;
		ncp_uint32_t byte_swap_enable    : 1;
		ncp_uint32_t status              : 2;
		ncp_uint32_t local_bit           : 1;
		ncp_uint32_t sysmem_access_type  : 4;
		ncp_uint32_t                     : 2;
		ncp_uint32_t start_done          : 1;
#else
		ncp_uint32_t start_done          : 1;
		ncp_uint32_t                     : 2;
		ncp_uint32_t sysmem_access_type  : 4;
		ncp_uint32_t local_bit           : 1;
		ncp_uint32_t status              : 2;
		ncp_uint32_t byte_swap_enable    : 1;
		ncp_uint32_t cfg_cmpl_int_enable : 1;
		ncp_uint32_t cmd_type            : 4;
		ncp_uint32_t dbs                 : 16;
#endif
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_0_t;

typedef union {
	ncp_uint32_t raw;
	struct {
		ncp_uint32_t target_address : 32;
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_1_t;

typedef union {
	ncp_uint32_t raw;
	struct {
#ifndef NCP_BIG_ENDIAN
		ncp_uint32_t target_id_address_upper : 8;
		ncp_uint32_t target_node_id          : 8;
		ncp_uint32_t                         : 16;
#else
		ncp_uint32_t                         : 16;
		ncp_uint32_t target_node_id          : 8;
		ncp_uint32_t target_id_address_upper : 8;
#endif
	} __attribute__ ( ( packed ) ) bits;
} __attribute__ ( ( packed ) ) command_data_register_2_t;


/*
  ------------------------------------------------------------------------------
  ncr_register_read
*/

static __inline__ ncp_uint32_t
ncr_register_read(unsigned long *address)
{
#ifdef NCP_NCA_BIG_ENDIAN
	return in_be32(address);
#else
	return readl(address);
#endif
}

/*
  ----------------------------------------------------------------------
  ncr_register_write
*/

static __inline__ void
ncr_register_write(const unsigned value, unsigned long *address)
{
#ifdef NCP_NCA_BIG_ENDIAN
	out_be32(address, value);
#else
	writel(value, address);
#endif
}

/*
  ------------------------------------------------------------------------------
  ncr_lock
*/

static int
ncr_lock(int domain)
{
#ifndef CONFIG_SPL_BUILD
	ncp_uint32_t offset;
	ncp_uint32_t value;
	int loops = 400000;

	offset=(0xff80 + (domain * 4));

	do {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		value = readl(POINTER(NCA + offset));
#else
		value = in_be32((unsigned *)(NCA + offset));
#endif
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
#ifndef CONFIG_SPL_BUILD
	ncp_uint32_t offset;

	offset=(0xff80 + (domain * 4));
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	writel(0, POINTER(NCA + offset));
#else
	out_be32((unsigned *)(NCA + offset), 0);
#endif
#endif
	return;
}

#if defined(CONFIG_AXXIA_55XX) || defined(CONFIG_AXXIA_55XX_EMU) || defined(CONFIG_AXXIA_SIM) || defined(CONFIG_AXXIA_56XX) || defined(CONFIG_AXXIA_56XX_EMU) || defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF) || defined(CONFIG_AXXIA_XLF_EMU) || defined(CONFIG_AXXIA_XLF_SIM)

/*
  -------------------------------------------------------------------------------
  ncr_read32_0x153
*/

static int
ncr_read32_0x153(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	ncp_uint32_t address;

	address = IO + 0x0 + (NCP_TARGET_ID(region) * 0x10) + offset;
	*value = readl(POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_0x153
*/

static int
ncr_write32_0x153(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	ncp_uint32_t address;

	address = IO + 0x0 + (NCP_TARGET_ID(region) * 0x10) + offset;
	writel(value, POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_read32_0x155
*/

static int
ncr_read32_0x155(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	ncp_uint32_t address;

	address = IO + 0x20000 + (NCP_TARGET_ID(region) * 0x800) + offset;
	*value = readl(POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_0x155
*/

static int
ncr_write32_0x155(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	ncp_uint32_t address;

	address = IO + 0x20000 + (NCP_TARGET_ID(region) * 0x800) + offset;
	writel(value, POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_read32_0x156
*/

static int
ncr_read32_0x156(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	ncp_uint32_t address;

	address = IO + 0x30000 + (NCP_TARGET_ID(region) * 0x1800) + offset;
	*value = readl(POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_0x156
*/

static int
ncr_write32_0x156(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	ncp_uint32_t address;

	address = IO + 0x30000 + (NCP_TARGET_ID(region) * 0x1800) + offset;
	writel(value, POINTER(address));

	return 0;
}
/*
  -------------------------------------------------------------------------------
  ncr_read32_0x158
*/

static int
ncr_read32_0x158(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	ncp_uint32_t address;

	address = IO + 0x60000 + offset;
	*value = readl(POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_0x158
*/

static int
ncr_write32_0x158(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	ncp_uint32_t address;

	address = IO + 0x60000 + offset;
	writel(value, POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_read32_0x159
*/

static int
ncr_read32_0x159(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	ncp_uint32_t address;

	address = IO + 0x70000 + offset;
	*value = readl(POINTER(address));

	return 0;
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_0x159
*/

static int
ncr_write32_0x159(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	ncp_uint32_t address;

	address = IO + 0x70000 + offset;
	writel(value, POINTER(address));

	return 0;
}

typedef struct
{
#ifdef NCP_NCA_BIG_ENDIAN
     unsigned      valid                                     :  1;
     unsigned      hwrite                                    :  1;
     unsigned      tshift                                    :  4;
     unsigned      hsize                                     :  3;
     unsigned      htrans                                    :  2;
     unsigned      reserved                                  :  5;
     unsigned      haddr                                     : 16;
#else    /* Little Endian */
     unsigned      haddr                                     : 16;
     unsigned      reserved                                  :  5;
     unsigned      htrans                                    :  2;
     unsigned      hsize                                     :  3;
     unsigned      tshift                                    :  4;
     unsigned      hwrite                                    :  1;
     unsigned      valid                                     :  1;
#endif
} ncp_apb2ser_indirect_Command1_reg_t;

static int
ncr_apb2ser_indirect_setup(
    ncp_uint32_t        regionId,
    ncp_uint32_t       *indirectOffset,
    ncp_uint32_t       *xferWidth)
{
    ncp_uint32_t    nodeId     = NCP_NODE_ID(regionId);
    ncp_uint32_t    tgtId      = NCP_TARGET_ID(regionId);
	ncp_uint32_t    baseId	= 0;

#ifdef CONFIG_AXXIA_56XX
	if ((nodeId < 0x110) || (nodeId > 0x11a))
		return -1;
#endif
#ifdef CONFIG_AXXIA_XLF
	if ((nodeId < 0x110) || (nodeId > 0x11f))
		return -1;
#endif

	/* For 56xx, target 0 is PHY config, target > 0 is serdes */
	*xferWidth = (tgtId > 0) ? 2 : 4;

	if (nodeId <= 0x114) {
		/* nodes 0x110 - 0x114 */
		baseId = (nodeId - 0x110) * 2;
	} else if (nodeId >= 0x116) {
		/* nodes 0x116 - 0x11a */
		baseId = (nodeId - 0x111) * 2;
	} else {
		/* node 0x115 */
		baseId = 0x14;
	}

	*indirectOffset = ((baseId + tgtId) * 0x10);

	return 0;
}


static int
ncr_apb2ser_indirect_access(
    ncp_uint32_t        offset,
    ncp_uint32_t        indirectOffset,
    ncp_uint32_t       *buffer,
    int                 isWrite,
    ncp_uint32_t        xferWidth)
{
    ncp_uint32_t reg;
    ncp_apb2ser_indirect_Command1_reg_t  *pCmd1 = 
                (ncp_apb2ser_indirect_Command1_reg_t *) &reg;
    ncp_uint32_t loop_count;

    /* build the command1 register */
    pCmd1->valid = 1;
    pCmd1->hwrite = isWrite;
    pCmd1->tshift = 1;
    pCmd1->htrans = 2; 
    pCmd1->hsize  = (xferWidth == 2) ? 1 : 2;
    pCmd1->haddr  = offset;

    if (isWrite)
    {
        /* write the data to be written */
	    writel(*buffer, POINTER(APB2_SER0_BASE + indirectOffset));
    }

    /* write command 1 */
    writel(reg, POINTER(APB2_SER0_BASE + indirectOffset + NCP_APB2SER_INDIRECT_COMMAND_1));
    
    /* poll for completion */
    loop_count = 400000;   /* TODO!! determine correct value! completely arbitrary for now */
    do {
        loop_count--;
        reg = readl(POINTER(APB2_SER0_BASE + indirectOffset + NCP_APB2SER_INDIRECT_COMMAND_1));
    } while (pCmd1->valid && loop_count);

    if (loop_count == 0) {
        return -1;
    }

    if (!isWrite) 
    {
	    *buffer = readl(POINTER(APB2_SER0_BASE + indirectOffset + NCP_APB2SER_INDIRECT_READ_DATA_0));
    }

    return 0;

}

/*
  -------------------------------------------------------------------------------
  ncr_read32_apb2ser
*/

static int
ncr_read32_apb2ser(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
    ncp_uint32_t indirectOffset = 0;
    ncp_uint32_t xferWidth = 0;

    if(ncr_apb2ser_indirect_setup(region, &indirectOffset, &xferWidth) == -1)
    {
        return -1;
    }

    return ncr_apb2ser_indirect_access(offset, indirectOffset,
        value, 0, xferWidth);
}

/*
  -------------------------------------------------------------------------------
  ncr_write32_apb2ser
*/

static int
ncr_write32_apb2ser(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
    ncp_uint32_t indirectOffset = 0;
    ncp_uint32_t xferWidth = 0;

    if(ncr_apb2ser_indirect_setup(region, &indirectOffset, &xferWidth) == -1)
    {
        return -1;
    }

    return ncr_apb2ser_indirect_access(offset, indirectOffset,
                &value, 1, xferWidth);

}


#endif	/* CONFIG_AXXIA_56XX */

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
ncr_read(ncp_uint32_t region,
	 ncp_uint32_t address_upper, ncp_uint32_t address,
	 int number, void *buffer)
{
	command_data_register_0_t cdr0;	/* 0x101.0.0xf0 */
	command_data_register_1_t cdr1;	/* 0x101.0.0xf4 */
	command_data_register_2_t cdr2;	/* 0x101.0.0xf8 */
	int wfc_timeout = WFC_TIMEOUT;

	if ((NCP_TARGET_ID(region) >= 0x110) &&
	    (NCP_TARGET_ID(region) <= 0x11f)) {
		return ncr_read32_apb2ser(region, address, buffer);
	}

	switch (NCP_NODE_ID(region)) {
	case 0x153:
		return ncr_read32_0x153(region, address, (ncp_uint32_t *)buffer);
		break;
	case 0x155:
		return ncr_read32_0x155(region, address, (ncp_uint32_t *)buffer);
		break;
	case 0x156:
		return ncr_read32_0x156(region, address, (ncp_uint32_t *)buffer);
		break;
	case 0x158:
		return ncr_read32_0x158(region, address, (ncp_uint32_t *)buffer);
		break;
	case 0x159:
		return ncr_read32_0x159(region, address, (ncp_uint32_t *)buffer);
		break;
	case 0x101:
	case 0x109:
	case 0x1d0:
	case 0x149:
	case 0x14f:
#if !defined(CONFIG_AXXIA_56XX) && \
  !defined(CONFIG_AXXIA_56XX_EMU) && \
  !defined(CONFIG_AXXIA_XLF) && \
  !defined(CONFIG_AXXIA_XLF_EMU) && \
  !defined(CONFIG_AXXIA_SIM)
		/*
		  If reading from within NCA/MME_POKE/SCB,
		  just do the plain and simple read
		*/
		if (NULL != buffer) {
			ncp_uint32_t offset = 0;

			if(NCP_NODE_ID(region) == 0x101) {
				offset = (NCA + address);
			} else if(NCP_NODE_ID(region) == 0x109) {
				offset = (MME_POKE + address);
			} else if(NCP_NODE_ID(region) == 0x1d0) {
				offset = (SCB + address);
			} else if (NCP_NODE_ID(region) == 0x149) {
				offset = (GPREG + address);
			} else if (NCP_NODE_ID(region) == 0x14f) {
				offset = (SRIO_GPREG + address);
			}

            

			while (4 <= number) {
				*((ncp_uint32_t *)buffer) =
					ncr_register_read(POINTER(offset));
				offset += 4;
				buffer += 4;
				number -= 4;
			}

			if (0 < number) {
				ncp_uint32_t temp;

				temp = ncr_register_read(POINTER(offset));
				memcpy(buffer, (void *)&temp, number);
			}
		}
#endif	/* Not 5600 */
		return 0;
		break;
	case 0x200:
		break;
	default:
		if(NCP_NODE_ID(region) >= 0x100) {
			printf("Unhandled read to 0x%lx.0x%lx.0x%lx\n",
			       (unsigned long)NCP_NODE_ID(region),
			       (unsigned long)NCP_TARGET_ID(region),
			       (unsigned long)address);
			return -1;
		}
		/* Actual config ring acces, continue. */
		break;
	}

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
	else {
		cdr2.bits.target_id_address_upper = address_upper;
	}

	ncr_register_write( cdr2.raw, POINTER ( NCA + NCP_NCA_CFG_PIO_CDR2 ) );

	cdr1.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, POINTER( NCA + NCP_NCA_CFG_PIO_CDR1 ) );

	cdr0.raw = 0;
	cdr0.bits.start_done = 1;

	if( 0xff == cdr2.bits.target_id_address_upper ) {
		cdr0.bits.local_bit = 1;
	}

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr0.bits.cmd_type = 0xc;
		cdr0.bits.sysmem_access_type = 2;
	} else {
		cdr0.bits.cmd_type = 0x4;
	}

	/* TODO: Verify number... */
	cdr0.bits.dbs = ( number - 1 );
	ncr_register_write( cdr0.raw, POINTER ( NCA + NCP_NCA_CFG_PIO_CDR0 ) );

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read( POINTER( NCA + NCP_NCA_CFG_PIO_CDR0 ) ) &
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

	if (0x3 !=
	    (ncr_register_read(POINTER(NCA + NCP_NCA_CFG_PIO_CDR0)) &
	     0x00c00000) >> 22) {
		ncr_unlock(LOCK_DOMAIN);
		return -1;
	}

	/*
	  Read the data into the buffer.
	*/

	if (NULL != buffer) {
		void *address;

		address = (void *)(NCA + NCP_NCA_CDAR_MEMORY_BASE);

		while (4 <= number) {
			*((ncp_uint32_t *)buffer) =
				ncr_register_read(POINTER(address));
			address += 4;
			number -= 4;
			buffer += 4;
		}

		if (0 < number) {
			ncp_uint32_t temp;

			temp = ncr_register_read(POINTER(address));
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
ncr_read8(ncp_uint32_t region, ncp_uint32_t offset, unsigned char *value)
{
	int rc;

	NCR_TRACE_READ8(region, offset);
	rc = ncr_read(region, 0, offset, 1, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_read16
*/

int
ncr_read16(ncp_uint32_t region, ncp_uint32_t offset, unsigned short *value)
{
	int rc = 0;

	NCR_TRACE_READ16(region, offset);

	rc = ncr_read(region, 0, offset, 2, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_read32
*/

int
ncr_read32(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t *value)
{
	int rc = 0;

	NCR_TRACE_READ32(region, offset);
	rc = ncr_read(region, 0, offset, 4, value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}


/*
  ------------------------------------------------------------------------------
  ncr_poll
*/

int
ncr_poll( ncp_uint32_t region, ncp_uint32_t offset,
	  ncp_uint32_t mask, ncp_uint32_t desired_value,
	  ncp_uint32_t delay_time, ncp_uint32_t delay_loops )
{
	int i;
	int rc = 0;

	NCR_TRACE_POLL(region, delay_loops, delay_time,
		       offset, mask, desired_value);

	for( i = 0; i < delay_loops; ++ i ) {
		ncp_uint32_t value;

		rc |= ncr_read(region, 0, offset, 4, &value);

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
ncr_write(ncp_uint32_t region,
	  ncp_uint32_t address_upper, ncp_uint32_t address,
	  int number, void *buffer)
{
	command_data_register_0_t cdr0;
	command_data_register_1_t cdr1;
	command_data_register_2_t cdr2;
	int dbs = (number - 1);
	int wfc_timeout = WFC_TIMEOUT;

	if ((NCP_TARGET_ID(region) >= 0x110) &&
	    (NCP_TARGET_ID(region) <= 0x11f)) {
		return ncr_write32_apb2ser(region, address,
					   *((ncp_uint32_t *)buffer));
	}
	switch (NCP_NODE_ID(region)) {
	case 0x153:
		return ncr_write32_0x153(region, address,
					 *((ncp_uint32_t *)buffer));
		break;
	case 0x155:
		return ncr_write32_0x155(region, address,
					 *((ncp_uint32_t *)buffer));
		break;
	case 0x156:
		return ncr_write32_0x156(region, address,
					 *((ncp_uint32_t *)buffer));
		break;
	case 0x158:
		return ncr_write32_0x158(region, address,
					 *((ncp_uint32_t *)buffer));
		break;
	case 0x159:
		return ncr_write32_0x159(region, address,
					 *((ncp_uint32_t *)buffer));
		break;
	case 0x101:
	case 0x109:
	case 0x1d0:
	case 0x149:
	case 0x14f:
#if !defined(CONFIG_AXXIA_56XX) && \
  !defined(CONFIG_AXXIA_56XX_EMU) && \
  !defined(CONFIG_AXXIA_XLF) && \
  !defined(CONFIG_AXXIA_XLF_EMU) && \
  !defined(CONFIG_AXXIA_SIM)
		if (NULL != buffer) {
			ncp_uint32_t offset = 0;

			if(NCP_NODE_ID(region) == 0x101) {
				offset = (NCA + address);
			} else if(NCP_NODE_ID(region) == 0x109) {
				offset = (MME_POKE + address);
			} else if(NCP_NODE_ID(region) == 0x1d0) {
				offset = (SCB + address);
			} else if (NCP_NODE_ID(region) == 0x149) {
				offset = (GPREG + address);
			} else if (NCP_NODE_ID(region) == 0x14f) {
				offset = (SRIO_GPREG + address);
			}

			while (4 <= number) {
				ncr_register_write(*((ncp_uint32_t *)buffer),
						   POINTER(offset));
				offset += 4;
				buffer += 4;
				number -= 4;
			}

			if (0 < number) {
				ncp_uint32_t temp;

				memcpy((void *)&temp, buffer, number);
				ncr_register_write(temp, POINTER(offset));
			}
		}
#endif	/* Not 5600 */
		return 0;
		break;
	case 0x200:
		break;
	default:
		if(NCP_NODE_ID(region) >= 0x100) {
			printf("Unhandled write to 0x%lx.0x%lx.0x%lx\n",
			       (unsigned long)NCP_NODE_ID(region),
			       (unsigned long)NCP_TARGET_ID(region),
			       (unsigned long)address);
			return -1;
		}
		/* Actual config ring acces, continue. */
		break;
	}

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
	else {
		cdr2.bits.target_id_address_upper = address_upper;
	}

	ncr_register_write( cdr2.raw, POINTER( NCA + NCP_NCA_CFG_PIO_CDR2 ) );

	cdr1.raw = 0;

	if( NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, POINTER(NCA + NCP_NCA_CFG_PIO_CDR1));

	/*
	  Copy data from the buffer.
	*/

	if (NULL != buffer) {
		void *offset;

		offset = (void *)(NCA + NCP_NCA_CDAR_MEMORY_BASE);

		while (4 <= number) {
			ncr_register_write(*((ncp_uint32_t *)buffer),
					   POINTER(offset));
			offset += 4;
			buffer += 4;
			number -= 4;
		}

		if (0 < number) {
			ncp_uint32_t temp;

			memcpy((void *)&temp, buffer, number);
			ncr_register_write(temp, POINTER(offset));
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
		cdr0.bits.sysmem_access_type = 2;
	} else {
		cdr0.bits.cmd_type = 0x5;
	}

	/* TODO: Verify number... */
	cdr0.bits.dbs = dbs;
	ncr_register_write(cdr0.raw, POINTER(NCA + NCP_NCA_CFG_PIO_CDR0));

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read(POINTER( NCA + NCP_NCA_CFG_PIO_CDR0 ) ) &
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

	if(0x3 !=
	   ((ncr_register_read(POINTER(NCA + NCP_NCA_CFG_PIO_CDR0)) & 0x00c00000) >> 22)) {
		printf("ncr_write( ) failed: 0x%lx, status1=0x%lx, status2=0x%lx\n",
		       (unsigned long)((ncr_register_read(POINTER(NCA +
								       NCP_NCA_CFG_PIO_CDR0)) &
					0x00c00000) >> 22),
		       (unsigned long)ncr_register_read(POINTER(NCA +
								     NCP_NCA_CFG_RING_ERROR_STAT_R0)),
		       (unsigned long)ncr_register_read(POINTER(NCA +
								     NCP_NCA_CFG_RING_ERROR_STAT_R1)));
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
ncr_write8( ncp_uint32_t region, ncp_uint32_t offset, unsigned char value )
{
	int rc;

	NCR_TRACE_WRITE8(region, offset, value);
	rc = ncr_write(region, 0, offset, 1, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write16
*/

int
ncr_write16( ncp_uint32_t region, ncp_uint32_t offset, unsigned short value )
{
	int rc;

	NCR_TRACE_WRITE16(region, offset, value);

	rc = ncr_write(region, 0, offset, 2, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_write32
*/

int
ncr_write32(ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value)
{
	int rc;

	NCR_TRACE_WRITE32(region, offset, value);
	rc = ncr_write(region, 0, offset, 4, &value);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncr_and
*/

int
ncr_and( ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value )
{
	ncp_uint32_t temp;
	int rc = 0;

	rc |= ncr_read(region, 0, offset, 4, &temp);
	temp &= value;
	rc |= ncr_write(region, 0, offset, 4, &temp);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  ncr_or
*/

int
ncr_or( ncp_uint32_t region, ncp_uint32_t offset, ncp_uint32_t value )
{
	ncp_uint32_t temp;
	int rc = 0;

	rc |= ncr_read(region, 0, offset, 4, &temp);
	temp |= value;
	rc |= ncr_write(region, 0, offset, 4, &temp);

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

/*
  ----------------------------------------------------------------------
  ncr_modify
*/

int
ncr_modify(ncp_uint32_t region, ncp_uint32_t address, int count,
	   void *masks, void *values)
{
	command_data_register_0_t cdr0;
	command_data_register_1_t cdr1;
	command_data_register_2_t cdr2;
	void *data_word_base;
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

	ncr_register_write( cdr2.raw, POINTER( NCA + NCP_NCA_CFG_PIO_CDR2 ) );

	cdr1.raw = 0;

	if(NCP_REGION_ID( 512, 1 ) == region ) {
		cdr1.bits.target_address = address;
	} else {
		cdr1.bits.target_address = ( address >> 2 );
	}

	ncr_register_write( cdr1.raw, POINTER( NCA + NCP_NCA_CFG_PIO_CDR1 ) );

	/*
	  Copy from buffer to the data words.
	*/

	data_word_base = (void *)(NCA + NCP_NCA_CDAR_MEMORY_BASE);
	ncr_register_write( count, POINTER(data_word_base ));
	data_word_base += 4;

	while( 0 < count ) {
		ncr_register_write( * ( ( ncp_uint32_t * ) masks ),
				    POINTER(data_word_base ));
		data_word_base += 4;
		ncr_register_write( * ( ( ncp_uint32_t * ) values ),
				    POINTER(data_word_base ));
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

	ncr_register_write(cdr0.raw, POINTER(NCA + NCP_NCA_CFG_PIO_CDR0));

	/*
	  Wait for completion.
	*/

	do {
		--wfc_timeout;
	} while( (0x80000000 ==
		  ( ncr_register_read(POINTER( NCA + NCP_NCA_CFG_PIO_CDR0 ) ) &
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
	    ( ( ncr_register_read(POINTER( NCA + NCP_NCA_CFG_PIO_CDR0 ) ) &
		0x00c00000 ) >> 22 ) ) {
#ifdef NCR_TRACER
		printf( "ncr_write( ) failed: 0x%x\n",
			( ( ncr_register_read(POINTER ( NCA + NCP_NCA_CFG_PIO_CDR0 ) ) &
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
ncr_modify32( ncp_uint32_t region, ncp_uint32_t offset,
	      ncp_uint32_t mask, ncp_uint32_t value )
{
	int rc;

	NCR_TRACE_MODIFY(region, offset, mask, value);
	rc = ncr_modify( region, offset, 1, & mask, & value );

	if (0 != rc)
		return ncr_fail(__FILE__, __FUNCTION__, __LINE__);

	return 0;
}

#ifdef SYSCACHE_ONLY_MODE

/*
  -------------------------------------------------------------------------------
  ncr_l3tags
*/

void
ncr_l3tags(void)
{
	int i;
	ncp_uint32_t address;

	/*donotwrite = 0;*/

	/*
	  ?
	*/

	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1000, 0x80000000);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1004, 0x0fffff00);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x1008, 0x00000020);
	ncr_write32(NCP_REGION_ID(0x16, 0x10), 0x100c, 0x00000000);

	/*
	  Set up cdar_memory
	*/

	for (i = 0; i < 64; ++i)
		writel(0, POINTER(NCA + NCP_NCA_CDAR_MEMORY_BASE + (i * 4)));

	/*
	  Write it
	*/

	address = 0;

	for (i = 0; i < (8 * 1024 * 1024) / 256; ++i, address += 256)
		ncr_write(NCP_REGION_ID(512, 1), 0x20, address, 256, NULL);

	return;
}

#endif
