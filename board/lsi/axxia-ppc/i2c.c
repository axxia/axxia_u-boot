/*
* i2c.c
*
* Basic I2C access using the custom LSI controller.
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

/*#define LSI_DEBUG*/
#define LSI_WARNING
/*#define LSI_LOGIO*/
#include <config.h>
#include <common.h>
#include <i2c.h>
#include <asm/io.h>

/*
============================================================================
============================================================================
Local
============================================================================
============================================================================
*/

#define SWAP32(value) ((((value) & 0x000000ff) << 24) | \
	(((value) & 0x0000ff00) <<  8)  | \
	(((value) & 0x00ff0000) >>  8)  | \
	(((value) & 0xff000000) >> 24))

#define I2C_STATUS_READ_DELAY 10000
#define I2C_MAX_TX_RETRIES 20
#define I2C_SINGLE_WRITE_SIZE 7

static unsigned long bus_speed = 1;
#ifndef AXM_35xx
static unsigned long mcc_value = 1;
#endif
static int initialized = -1;
static int i2c_bus_num = -1;

#ifdef AXM_35xx
/* Desired SCL timeout (ns) */
#define SCL_LOW_TIMEOUT (25000000)

#define MST_STATUS_RFL (1<<13) /* RX FIFO serivce */
#define MST_STATUS_TFL (1<<12) /* TX FIFO service */
#define MST_STATUS_SNS (1<<11) /* Manual mode done */
#define MST_STATUS_SS  (1<<10) /* Automatic mode done */
#define MST_STATUS_SCC (1<<9)  /* Stop complete */
#define MST_STATUS_TSS (1<<7)  /* Timeout */
#define MST_STATUS_AL  (1<<6)  /* Arbitration lost */
#define MST_STATUS_NAK (MST_STATUS_NA | MST_STATUS_ND)
#define MST_STATUS_ND  (1<<5)  /* NAK on data phase */
#define MST_STATUS_NA  (1<<4)  /* NAK on address phase */
#define MST_STATUS_ERR (MST_STATUS_NAK | MST_STATUS_AL | MST_STATUS_TSS)

#define CHIP_READ(_chip)  ((chip << 1) | 1)
#define CHIP_WRITE(_chip) ((chip << 1) | 0)

/*
* ns_to_clk - Convert nanoseconds to clock cycles for the given clock
* frequency.
*/
static unsigned long
ns_to_clk(unsigned long long ns, unsigned long clk_mhz)
{
	return lldiv(ns*clk_mhz, 1000);
}

static int
i2c_initialized(void)
{
	if (!(initialized & (1<<i2c_bus_num))) {
		printf("I2C dev %d not initialized\n", i2c_bus_num);
		return 0;
	}
	return 1;
}

#endif

/*
* i2c_base_addr - Return the I2C controller base address for currently
* selected bus.
*/
static unsigned long
i2c_base_addr(void)
{
	unsigned long i2c_addr = I2C0;

#ifdef CONFIG_I2C_MULTI_BUS
	switch (i2c_get_bus_num()) {
	case 0:
		i2c_addr = I2C0;
		break;
	case 1:
		i2c_addr = I2C1;
		break;
#ifndef ACP_25xx
	case 2:
		i2c_addr = I2C2;
		break;
	case 3:
		i2c_addr = I2C3;
		break;
#endif
	default:
		return 0;
	}
#endif
	return i2c_addr;
}



#ifndef AXM_35xx
/*
-------------------------------------------------------------------------------
_i2c_write
*/

static int
_i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr = i2c_base_addr();
	unsigned int bus_num;

	DEBUG_PRINT("chip=0x%x/%d addr=%u alen=%d len=%d\n",
		    chip, chip, addr, alen, len);

	while (0 < len) {
		unsigned long status;
		unsigned long control;
		unsigned long value[2] = {0, 0};
		uchar *input = (uchar *)value;
		int this_len;
		int i;
		int retries;

		if (I2C_SINGLE_WRITE_SIZE <= len)
			this_len = I2C_SINGLE_WRITE_SIZE;
		else
			this_len = len;

		++this_len;
		DEBUG_PRINT("len=%d this_len=%d addr=%d buffer=0x%p\n",
			    len, this_len, addr, buffer);

		/* stop, moc, mma */
		if (2 == alen)
			WRITEL(0x20000580, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000500, i2c_addr + I2C_MTC);

		/* constants for clocks... */
		WRITEL(mcc_value, i2c_addr + I2C_MCC);
		WRITEL(0x00800000, i2c_addr + I2C_MSTSHC);
		WRITEL(0x00000080, i2c_addr + I2C_MSPSHC);
		WRITEL(0x00140014, i2c_addr + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			WRITEL(0x20000100, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000180, i2c_addr + I2C_MTC);

		WRITEL(chip, i2c_addr + I2C_MSLVADDR);

		memset(input, 0, sizeof(input));
		DEBUG_PRINT("buffer[] = " \
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n" \
			    "input[]  = " \
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n", \
			    buffer[0], buffer[1], buffer[2], buffer[3],
			    buffer[4], buffer[5], buffer[6], buffer[7],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7]);
		input[(8 - this_len)] = addr;
		DEBUG_PRINT("this_len=%d input[%d]=0x%x\n",
			    this_len, (8 - this_len), input[(8 - this_len)]);

		for (i = (8 - this_len + 1); i < 8; ++i) {
			input[i] = *buffer++;
			DEBUG_PRINT("input[%d]=0x%x\n", i, input[i]);
		}

		DEBUG_PRINT("buffer[] = " \
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n" \
			    "input[]  = " \
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n" \
			    "value[] = " \
			    "{0x%08lx 0x%08lx}\n" \
			    buffer[0], buffer[1], buffer[2], buffer[3],
			    buffer[4], buffer[5], buffer[6], buffer[7],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7],
			    value[0], value[1]);
		WRITEL(value[1], i2c_addr + I2C_TXD0);
		WRITEL(value[0], i2c_addr + I2C_TXD1);

		/* stop, mma, this_len bytes, tr */
		if (2 == alen)
			control = 0x20000181 | (this_len << 1);
		else
			control = 0x20000101 | (this_len << 1);

		WRITEL(control, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(i2c_addr + I2C_MTS);
			--retries;
		} while ((0 == status) && (0 < retries));

		if ((1 != status) || (0 == retries))
			return -1;

		--this_len;
		len -= this_len;
		addr += this_len;
	}

	return 0;
}
#endif

/*
===============================================================================
===============================================================================
Global
===============================================================================
===============================================================================
*/

/*
-------------------------------------------------------------------------------
i2c_init
*/

void
i2c_init(int speed, int slaveadd)
{

#ifndef AXM_35xx
	i2c_set_bus_speed(speed);
	initialized = 1;
#else
	unsigned long i2c_addr = i2c_base_addr();

	DEBUG_PRINT("i2c_init: speed=%d slave=%#x\n", speed, slave);

	/* Enable Master Mode */
	writel(0x1, i2c_addr + AI2C_REG_I2C_GLOBAL_CONTROL);

	i2c_set_bus_speed(speed);

	initialized |= (1<<i2c_bus_num);

#endif

	return;
}

#ifdef CONFIG_I2C_MULTI_BUS
int i2c_set_bus_num(unsigned int bus)
{
	if (bus < CONFIG_SYS_MAX_I2C_BUS) {
		i2c_bus_num = bus;
		i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
	} else {
		return -1;
	}
	return 0;
}

unsigned int i2c_get_bus_num(void)
{
	if (i2c_bus_num == -1)
		i2c_bus_num = 0;

	return i2c_bus_num;
}
#endif

/*
-------------------------------------------------------------------------------
i2c_set_bus_speed
*/

int
i2c_set_bus_speed(unsigned int speed)
{
	unsigned long per_clock;
	unsigned long divisor;
	unsigned long load_value;
#ifdef AXM_35xx
	unsigned long clk_mhz;
	unsigned long t_setup;
	unsigned long i2c_addr = i2c_base_addr();
#endif

#ifndef AXM_35xx
	load_value = 49;

#ifdef CONFIG_I2C_MULTI_BUS
	if (i2c_get_bus_num() == 0) {
		printf("setting TIMER0\n");
		WRITEL(0, (TIMER0 + TIMER_CONTROL));
		WRITEL(load_value, (TIMER0 + TIMER_LOAD));
		WRITEL(load_value, (TIMER0 + TIMER_VALUE));
		WRITEL(0xc0, (TIMER0 + TIMER_CONTROL));
	} else if (i2c_get_bus_num() == 1) {
		printf("setting TIMER1\n");
		WRITEL(0, (TIMER1 + TIMER_CONTROL));
		WRITEL(load_value, (TIMER1 + TIMER_LOAD));
		WRITEL(load_value, (TIMER1 + TIMER_VALUE));
		WRITEL(0xc0, (TIMER1 + TIMER_CONTROL));
	}
#else
	printf("setting TIMER1\n");
	WRITEL(0, (TIMER1 + TIMER_CONTROL));
	WRITEL(load_value, (TIMER1 + TIMER_LOAD));
	WRITEL(load_value, (TIMER1 + TIMER_VALUE));
	WRITEL(0xc0, (TIMER1 + TIMER_CONTROL));
#endif

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

	divisor = per_clock / speed;

	/*
	  High and low clocks can each last up to 1023 input clocks.
	  So, the maximum divisor would be 2046 (BUT, 2044 is the
	  highest value that works...).
	*/

#define I2C_MAXIMUM_DIVISOR 2044

	if ((I2C_MAXIMUM_DIVISOR < divisor) ||
	    (0 == speed)) {
		printf("Minimum Available Speed is %lu\n",
		       (per_clock / I2C_MAXIMUM_DIVISOR));
		return -1;
	}

	mcc_value = (divisor / 2);
	mcc_value |= ((divisor - mcc_value) << 16);
	bus_speed = per_clock /
		((mcc_value & 0x3ff) + ((mcc_value & 0x03ff0000) >> 16));
	DEBUG_PRINT("per_clock=%lu divisor=%lu mcc_value=0x%x bus_speed=%lu\n",
		    per_clock, divisor, mcc_value, bus_speed);
#else
	bus_speed = speed;

	if (acp_clock_get(clock_peripheral, &per_clock) < 0) {
		printf("Failed to retreive peripheral clock speed\n");
		return -1;
	}

	divisor = per_clock / (speed/1000);
	clk_mhz = per_clock / 1000;

	DEBUG_PRINT("i2c_set_bus_speed: per_clk=%luMHz -> ratio=1:%lu\n",
		clk_mhz, divisor);

	/* SCL High Time */
	WRITEL(divisor/2, i2c_addr + AI2C_REG_I2C_SCL_HIGH_PERIOD);
	/* SCL Low Time */
	WRITEL(divisor/2, i2c_addr + AI2C_REG_I2C_SCL_LOW_PERIOD);

	if (speed <= 100000) {
		/* Standard mode tSU:DAT = 250 ns */
		t_setup = ns_to_clk(250, clk_mhz);
	} else {
		/* Fast mode tSU:DAT = 100 ns */
		t_setup = ns_to_clk(100, clk_mhz);
	}

	/* SDA Setup Time */
	WRITEL(t_setup, i2c_addr + AI2C_REG_I2C_SDA_SETUP_TIME);

	/* SDA Hold Time, 5ns */
	WRITEL(ns_to_clk(5, clk_mhz), i2c_addr + AI2C_REG_I2C_SDA_HOLD_TIME);

	/* Filter > 50ns spikes */
	WRITEL(ns_to_clk(50, clk_mhz), i2c_addr + AI2C_REG_I2C_SPIKE_FLTR_LEN);

	/* Configure Time-Out Registers. Find a prescaler value that make the
	 * timeout value fit into the 15-bit counter register.
	 */
	{
		unsigned int tmo_clk = ns_to_clk(SCL_LOW_TIMEOUT, clk_mhz);
		unsigned int prescale = 0; /* log2 of the prescale divider */

		while (tmo_clk > 0x7fff && prescale < 15) {
			++prescale;
			tmo_clk >>= 1;
		}

		if (tmo_clk > 0x7fff)
			tmo_clk = 0x7fff;

		DEBUG_PRINT("i2c: tmo_clk %u, divider %u\n",
			tmo_clk, 1<<prescale);
		WRITEL(prescale, i2c_addr + AI2C_REG_I2C_TIMER_CLOCK_DIV);
		WRITEL((1<<15) | tmo_clk,
			i2c_addr + AI2C_REG_I2C_WAIT_TIMER_CONTROL);
	}

	DEBUG_PRINT("i2c: SDA_SETUP:        %08x\n",
	READL(i2c_addr+AI2C_REG_I2C_SDA_SETUP_TIME));
	DEBUG_PRINT("i2c: SDA_HOLD:         %08x\n",
	READL(i2c_addr+AI2C_REG_I2C_SDA_HOLD_TIME));
	DEBUG_PRINT("i2c: SPIKE_FILTER_LEN: %08x\n",
	READL(i2c_addr+AI2C_REG_I2C_SPIKE_FLTR_LEN));
	DEBUG_PRINT("i2c: TIMER_DIV:        %08x\n",
	READL(i2c_addr+AI2C_REG_I2C_TIMER_CLOCK_DIV));
	DEBUG_PRINT("i2c: WAIT_TIMER:       %08x\n",
	READL(i2c_addr+AI2C_REG_I2C_WAIT_TIMER_CONTROL));

#endif

	return 0;
}

/*
-------------------------------------------------------------------------------
i2c_get_bus_speed
*/

unsigned int
i2c_get_bus_speed(void)
{
	if (0 == initialized) {
		ERROR_PRINT("I2C has not been initialized!\n");
		return 0;
	}

	return bus_speed;
}


#ifdef AXM_35xx
/*
* i2c_addr_to_buf - Convert 32-bit integer to uchar buffer.
*/
static void
i2c_addr_to_buf(uint addr, int alen, uchar *abuf)
{
	while (--alen >= 0) {
		abuf[alen] = addr & 0xff;
		addr >>= 8;
	}
}

/*
 * i2c_check_status - Check status of the current transfer.
 * Return -1 on transfer error.
 */
static int
i2c_check_status(unsigned int status, unsigned int *acc_status)
{
	if (status & MST_STATUS_ERR) {
		DEBUG_PRINT("i2c: transfer ABORTED (status %#x/%#x)\n",
			status, *acc_status);
		return -1;
	}
	if (status & MST_STATUS_SNS)
		*acc_status |= MST_STATUS_SNS;

	if (status & MST_STATUS_SCC)
		*acc_status |= MST_STATUS_SCC;

	return 0;
}

/*
* i2c_stop - Generate STOP on the I2C bus to terminate a transaction.
*/
int
i2c_stop(unsigned long i2c_addr)
{
	int rc;
	unsigned int status;
	unsigned int acc_status = 0;
	unsigned int done_bits = MST_STATUS_SCC;

	WRITEL(0xb, i2c_addr + AI2C_REG_I2C_MST_COMMAND);

	while (acc_status != done_bits) {
		status = READL(i2c_addr + AI2C_REG_I2C_MST_INT_STATUS);
		rc = i2c_check_status(status, &acc_status);
		if (rc < 0)
			break;
	}

	return rc;
}

/*
 * i2c_write_bytes - Perform single I2C write.
 *
 * <START> <chip_addr R/nW=0> <addr[0]> ... <addr[len-1]>
 *                    <data[0]> <data[1]> ... <data[len-1]>
 */
int
i2c_write_bytes(unsigned long i2c_addr, uchar chip,
		const uchar *addr, int alen,
		const uchar *data, int dlen)
{
	int result = 0;
	int len = alen + dlen;
	unsigned int status;
	unsigned int acc_status = 0; /* Accumulated status bits to determine
				      * when transfer is complete */
	unsigned int done_bits = MST_STATUS_SNS;

	DEBUG_PRINT("i2c_write_bytes: chip=%#x, addr=[%02x %02x]"\
		"alen=%d buffer=[%02x %02x %02x %02x], len=%d\n",\
		chip, addr[0], addr[1], alen, data[0], data[1],
		data[2], data[3], len);

	/* TX # bytes */
	WRITEL(len, i2c_addr + AI2C_REG_I2C_MST_TX_XFER);
	/* RX 0 bytes */
	WRITEL(0, i2c_addr + AI2C_REG_I2C_MST_RX_XFER);
	/* Chip address for write */
	WRITEL(CHIP_WRITE(chip), i2c_addr + AI2C_REG_I2C_MST_ADDR_1);

	/* Start manual mode without stop */
	WRITEL(0x8, i2c_addr + AI2C_REG_I2C_MST_COMMAND);

	while (acc_status != done_bits) {
		status = READL(i2c_addr + AI2C_REG_I2C_MST_INT_STATUS);

		if (status & MST_STATUS_TFL) {
			/* Data to TX FIFO (at least five bytes of space) */
			int i;
			for (i = 0; i < 5 && len > 0; i++) {
				unsigned txbyte = 0;
				if (alen > 0) {
					txbyte = *addr++;
					--alen;
				} else {
					txbyte = *data++;
				}
				WRITEL(txbyte,
					i2c_addr + AI2C_REG_I2C_MST_DATA);
				--len;
			}
		}
		result = i2c_check_status(status, &acc_status);
		if (result < 0)
			break;
	}

	/* Wait for state machine to go IDLE */
	while (READL(i2c_addr + AI2C_REG_I2C_MST_COMMAND) & 0x8)
		;

	DEBUG_PRINT("i2c_write: transfer finished, xfr_rx=%u/%u xfr_tx=%u/%u\n",
	READL(i2c_addr + AI2C_REG_I2C_MST_RX_XFER),
	READL(i2c_addr + AI2C_REG_I2C_MST_RX_BYTES_XFRD),
	READL(i2c_addr + AI2C_REG_I2C_MST_TX_XFER),
	READL(i2c_addr + AI2C_REG_I2C_MST_TX_BYTES_XFRD));

	return result;
}

/*
* i2c_read_bytes - Performs a single I2C read.
*
* <START> <chip_addr R/nW=1> <buffer[0]> <buffer[1]> ... <buffer[len-1]>
*/
int
i2c_read_bytes(unsigned long i2c_addr, uchar chip, uchar *buffer, int len)
{
	int result = 0;
	unsigned int status;
	unsigned int acc_status = 0; /* Accumulated status bits to determine
				      * when transfer is complete */
	unsigned int done_bits = MST_STATUS_SNS;

	/* Read 'len' bytes */
	WRITEL(len, i2c_addr + AI2C_REG_I2C_MST_RX_XFER);
	/* Will transmit zero bytes */
	WRITEL(0, i2c_addr + AI2C_REG_I2C_MST_TX_XFER);
	/* Chip address for read */
	WRITEL(CHIP_READ(chip), i2c_addr + AI2C_REG_I2C_MST_ADDR_1);

	/* Start manual mode without stop */
	WRITEL(0x8, i2c_addr + AI2C_REG_I2C_MST_COMMAND);

	while (acc_status != done_bits) {
		status = READL(i2c_addr + AI2C_REG_I2C_MST_INT_STATUS);

		if (status & MST_STATUS_RFL) {
			/* Data in RX FIFO */
			*buffer++ = READL(i2c_addr + AI2C_REG_I2C_MST_DATA);
			--len;
		}
		result = i2c_check_status(status, &acc_status);
		if (result < 0)
			break;
	}

	while (READL(i2c_addr + AI2C_REG_I2C_MST_RX_FIFO) > 0) {
		*buffer++ = READL(i2c_addr + AI2C_REG_I2C_MST_DATA);
		--len;
	}

	/* Wait for state machine to go IDLE */
	while (READL(i2c_addr + AI2C_REG_I2C_MST_COMMAND) & 0x8)
		;

	DEBUG_PRINT("i2c_read: transfer finished, xfr_rx=%u/%u xfr_tx=%u/%u\n",
	READL(i2c_addr + AI2C_REG_I2C_MST_RX_XFER),
	READL(i2c_addr + AI2C_REG_I2C_MST_RX_BYTES_XFRD),
	READL(i2c_addr + AI2C_REG_I2C_MST_TX_XFER),
	READL(i2c_addr + AI2C_REG_I2C_MST_TX_BYTES_XFRD));

	return result;
}

#endif

/*
-------------------------------------------------------------------------------
i2c_probe
*/

int
i2c_probe(uchar chip)
{
#ifndef AXM_35xx
	uchar buffer[8];
	int rc;

	if (0 == initialized)
		return -1;

	memset(buffer, 0, sizeof(buffer));
	rc = i2c_read(chip, 0, 1, buffer, 4);

	if (0 == rc)
		return 0;

	return -1;
#else
	unsigned long i2c_addr = i2c_base_addr();
	int rc;
	uchar dummy;


	if (!i2c_initialized())
		return -1;

	rc = i2c_read_bytes(i2c_addr, chip, &dummy, 1);
	i2c_stop(i2c_addr);

	return rc;

#endif
}

/*
-------------------------------------------------------------------------------
i2c_read
*/

int
i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr = i2c_base_addr();
	int rc;

	if (0 == initialized)
		return -1;

	if (0 == alen) {
		printf("Unsupported address length!  " \
		       "Only .1 and .2 are supported.\n");
		return -1;
	}

	DEBUG_PRINT("chip=0x%x/%d addr=%u alen=%d len=%d\n",
		    chip, chip, addr, alen, len);

#ifndef AXM_35xx
	while (0 < len) {
		unsigned long status;
		unsigned long value[2];
		uchar *input = (uchar *)value;
		int this_len;
		int retries;

		if (8 <= len)
			this_len = 8;
		else
			this_len = len;

		/* stop, moc, mma */
		if (2 == alen)
			WRITEL(0x20000580, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000500, i2c_addr + I2C_MTC);

		/* constants for clocks... */
		WRITEL(mcc_value, i2c_addr + I2C_MCC);
		WRITEL(0x00800000, i2c_addr + I2C_MSTSHC);
		WRITEL(0x00000080, i2c_addr + I2C_MSPSHC);
		WRITEL(0x00140014, i2c_addr + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			WRITEL(0x20000180, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000100, i2c_addr + I2C_MTC);

		WRITEL(chip, i2c_addr + I2C_MSLVADDR);

		WRITEL(addr, i2c_addr + I2C_TXD0);
		WRITEL(0x00000000, i2c_addr + I2C_TXD1);

		/* stop, mma, one byte, tr */
		if (2 == alen)
			WRITEL(0x20000183, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000103, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(i2c_addr + I2C_MTS);
			--retries;
		} while ((0 == status) && (0 < retries));

		if ((1 != status) || (0 == retries))
			return -1;

		if (2 == alen)
			WRITEL(0x20000580, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000500, i2c_addr + I2C_MTC);

		WRITEL(mcc_value, i2c_addr + I2C_MCC);
		WRITEL(0x00800000, i2c_addr + I2C_MSTSHC);
		WRITEL(0x00000080, i2c_addr + I2C_MSPSHC);
		WRITEL(0x00140014, i2c_addr + I2C_MDSHC);
		WRITEL(0x00000000, i2c_addr + I2C_MIE);

		if (2 == alen)
			WRITEL(0x20000180, i2c_addr + I2C_MTC);
		else
			WRITEL(0x20000100, i2c_addr + I2C_MTC);

		WRITEL(chip, i2c_addr + I2C_MSLVADDR);
		WRITEL((this_len << 1) | 1, i2c_addr + I2C_MRC);
		WRITEL(0x20000301, i2c_addr + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		do {
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(i2c_addr + I2C_MRS);
		} while (1 != (status & 1));

		if (1 != (status & 0x3))
			return -1;

		value[1] = READL(i2c_addr + I2C_RXD0);
		value[0] = READL(i2c_addr + I2C_RXD1);
		DEBUG_PRINT("value[] = {0x%lx 0x%lx}\n"
			    "input[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
			    value[0], value[1],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7]);
		input += (8 - this_len);
		memcpy(buffer, input, this_len);
		len -= this_len;
		buffer += this_len;
		addr += this_len;
	}
#else
	/* Send address */
	if (alen > 0) {
		uchar abuf[4];
		i2c_addr_to_buf(addr, alen, abuf);
		if (i2c_write_bytes(i2c_addr, chip, NULL, 0, abuf, alen) < 0)
			return -1;
	}

	if (len == 0)
		return 0;

	rc = i2c_read_bytes(i2c_addr, chip, buffer, len);
	i2c_stop(i2c_addr);
#endif

	return 0;
}

/*
-------------------------------------------------------------------------------
i2c_write
*/

#define CHUNK_SIZE 4

int
i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	int rc;
	unsigned long i2c_addr = i2c_base_addr();

	if (0 == initialized)
		return -1;

#ifndef AXM_35xx

	while (CHUNK_SIZE < len) {
		rc = _i2c_write(chip, addr, alen, buffer, CHUNK_SIZE);

		if (0 != rc)
			return rc;

		addr += CHUNK_SIZE;
		buffer += CHUNK_SIZE;
		len -= CHUNK_SIZE;
	}

	return _i2c_write(chip, addr, alen, buffer, len);

#else
	if (alen > 0) {
		uchar abuf[4];
		i2c_addr_to_buf(addr, alen, abuf);
		rc =  i2c_write_bytes(i2c_addr, chip, abuf, alen, buffer, len);
	} else {
		rc = i2c_write_bytes(i2c_addr, chip, NULL, 0, buffer, len);
	}

	i2c_stop(i2c_addr);

	return rc;
#endif
}
