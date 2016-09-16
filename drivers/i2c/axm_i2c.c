/*
 *  Copyright (C) 2016 Intel (john.jacques@intel.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 */

#include <common.h>
#include <asm/io.h>
#include <div64.h>
#include <i2c.h>

/* Desired SCL timeout (ns) */
#define SCL_LOW_TIMEOUT (25000000)

static unsigned int current_speed;
static unsigned int current_bus;
static unsigned int initialized;

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

#define CHIP_READ(chip)  (((chip) << 1) | 1)
#define CHIP_WRITE(chip) (((chip) << 1) | 0)

/*
  ------------------------------------------------------------------------------
  ns_to_clk

  Convert nanoseconds to clock cycles for the given clock frequency.
*/

static unsigned int
ns_to_clk(unsigned int ns, unsigned int clk_mhz)
{
	debug("%s:%d - ns=%u clk_mhz=%u return=%u\n",
	      __FILE__, __LINE__, ns, clk_mhz, (ns * (clk_mhz / 1000)));

	return ns * (clk_mhz / 1000);
}

/*
  ------------------------------------------------------------------------------
  i2c_base_addr

  Return the I2C controller base address for currently selected bus.
*/

static void *
i2c_base_addr(void)
{
	void *i2c_addr = NULL;

#if defined(CONFIG_I2C_MULTI_BUS)
	switch (i2c_get_bus_num()) {
	case 0:
		i2c_addr = (void *)I2C0;
		break;
	case 1:
		i2c_addr = (void *)I2C1;
		break;
	case 2:
		i2c_addr = (void *)I2C2;
		break;
	case 3:
		i2c_addr = (void *)I2C3;
		break;
#if defined(CONFIG_AXXIA_ANY_XLF)
	case 4:
		i2c_addr = (void *)I2C4;
		break;
	case 5:
		i2c_addr = (void *)I2C5;
		break;
	case 6:
		i2c_addr = (void *)I2C6;
		break;
	case 7:
		i2c_addr = (void *)I2C7;
		break;
	case 8:
		i2c_addr = (void *)I2C8;
		break;
	case 9:
		i2c_addr = (void *)I2C9;
		break;
	case 10:
		i2c_addr = (void *)I2C10;
		break;
	case 11:
		i2c_addr = (void *)I2C11;
		break;
	case 12:
		i2c_addr = (void *)I2C12;
		break;
#endif	/* CONFIG_AXXIA_ANY_XLF */
	default:
		break;
	}
#else  /* CONFIG_I2C_MULTI_BUS */
	i2c_addr = (void *)I2C0;
#endif  /* CONFIG_I2C_MULTI_BUS */

	debug("%s:%d - returning 0x%p\n", __FILE__, __LINE__, i2c_addr);

	return i2c_addr;
}

/*
  ------------------------------------------------------------------------------
  i2c_initialized
*/

static int
i2c_initialized(void)
{
	if (!(initialized & (1 << current_bus))) {
		printf("I2C dev %d is not initialized\n", current_bus);

		return 0;
	}

	return 1;
}

/*
  ------------------------------------------------------------------------------
  i2c_check_status

  Check status of the current transfer.  Return -1 on transfer error.
*/

static int
i2c_check_status(unsigned int status, unsigned int *acc_status)
{
	if (status & MST_STATUS_ERR)
		return -1;

	if (status & MST_STATUS_SNS)
		*acc_status |= MST_STATUS_SNS;

	if (status & MST_STATUS_SCC)
		*acc_status |= MST_STATUS_SCC;

	debug("%s:%d - *acc_status=0x%x\n", __FILE__, __LINE__, *acc_status);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  i2c_addr_to_buf

  Convert 32-bit integer to uchar buffer.
*/

static void
i2c_addr_to_buf(unsigned int addr, int alen, unsigned char *abuf)
{
	while (--alen >= 0) {
		abuf[alen] = addr & 0xff;
		addr >>= 8;
	}
}

/*
  ------------------------------------------------------------------------------
  i2c_write_bytes

  Perform single I2C write.

  <START> <chip_addr R/nW=0>
  <addr[0]> <addr[1]> ... <addr[len-1]>
  <data[0]> <data[1]> ... <data[len-1]>
*/

static int
i2c_write_bytes(void *i2c_addr, unsigned char chip,
		const uchar *addr, int alen,
		const uchar *data, int dlen)
{
	int result = 0;
	int len = alen + dlen;
	unsigned int status;
	/* Accumulated status bits to determine when transfer is complete. */
	unsigned int acc_status = 0;
	unsigned int done_bits = MST_STATUS_SNS;

	debug("%s:%d - i2c_addr=0x%p chip=%u alen=%d dlen=%d\n",
	      __FILE__, __LINE__, i2c_addr, chip, alen, dlen);

	/* TX # bytes */
	writel(len, i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER);

	/* RX 0 bytes */
	writel(0, i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER);

	/* Chip address for write */
	writel(CHIP_WRITE(chip), i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);

	/* Start manual mode without stop */
	writel(0x8, i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND);

	while (acc_status != done_bits) {
		status = readl(i2c_addr + AI2C_REG_I2C_X7_MST_INT_STATUS);

		if (status & MST_STATUS_TFL) {
			/* Data to TX FIFO (at least five bytes of space) */
			int i;
		
			for (i = 0; i < 5 && len > 0; i++) {
				unsigned int txbyte = 0;

				if (alen > 0) {
					txbyte = *addr++;
					--alen;
				} else {
					txbyte = *data++;
				}

				writel(txbyte,
				       i2c_addr + AI2C_REG_I2C_X7_MST_DATA);
				--len;
			}
		}

		result = i2c_check_status(status, &acc_status);

		if (result < 0)
			return -1;
	}

	/* Wait for state machine to go IDLE */
	while (readl(i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND) & 0x8)
		;

	debug("%s:%d - transfer finished, xfr_rx=%u/%u xfr_tx=%u/%u\n",
	      __FILE__, __LINE__,
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_BYTES_XFRD),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD));

	return result;
}

/*
  ------------------------------------------------------------------------------
  i2c_read_bytes

  Performs a single I2C read.

  <START> <chip_addr R/nW=1> <buffer[0]> <buffer[1]> ... <buffer[len-1]>
*/

int
i2c_read_bytes(void *i2c_addr, uchar chip, unsigned char *buffer, int len)
{
	int result = 0;
	unsigned int status;
	/* Accumulated status bitsto determine when transfer is complete. */
	unsigned int acc_status = 0;
	unsigned int done_bits = MST_STATUS_SNS;

	/* Read 'len' bytes */
	writel(len, i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER);
	/* Will transmit zero bytes */
	writel(0, i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER);
	/* Chip address for read */
	writel(CHIP_READ(chip), i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);

	/* Start manual mode without stop */
	writel(0x8, i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND);

	while (acc_status != done_bits) {
		status = readl(i2c_addr + AI2C_REG_I2C_X7_MST_INT_STATUS);

		if (status & MST_STATUS_RFL) {
			/* Data in RX FIFO */
			*buffer++ = readl(i2c_addr + AI2C_REG_I2C_X7_MST_DATA);
			--len;
		}
		result = i2c_check_status(status, &acc_status);
		if (result < 0)
			break;
	}

	while (readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_FIFO) > 0) {
		*buffer++ = readl(i2c_addr + AI2C_REG_I2C_X7_MST_DATA);
		--len;
	}

	/* Wait for state machine to go IDLE */
	while (readl(i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND) & 0x8)
		;

	debug("i2c_read: transfer finished, xfr_rx=%u/%u xfr_tx=%u/%u\n",
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_BYTES_XFRD),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD));

	return result;
}


/*
  ------------------------------------------------------------------------------
  i2c_stop

  Generate STOP on the I2C bus to terminate a transaction.
*/

static int
i2c_stop(void *i2c_addr)
{
	int rc = 0;
	unsigned int status;
	unsigned int acc_status = 0;
	unsigned int done_bits = MST_STATUS_SCC;

	writel(0xb, i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND);

	while (acc_status != done_bits) {
		status = readl(i2c_addr + AI2C_REG_I2C_X7_MST_INT_STATUS);
		rc = i2c_check_status(status, &acc_status);

		if (rc < 0)
			break;
	}

	return rc;
}

/*
  ==============================================================================
  ==============================================================================
  U-Boot Interface
  ==============================================================================
  ==============================================================================
*/


/*
 * i2c_read
 */
int
i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	void *i2c_addr = i2c_base_addr();
	int rc;

	if (!i2c_initialized())
		return -1;

	if (i2c_addr == 0)
		printf("Unsupported bus (%d)\n", i2c_get_bus_num());

	if (len > 255) {
		printf("Unsuppoted transfer length (max 255)\n");
		return -1;
	}

	debug("i2c_read: chip=%#x, addr=%#x, alen=%d, len=%d\n",
	      chip, addr, alen, len);

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

	return rc;
}

/*
 * i2c_write
 */
int
i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	void *i2c_addr = i2c_base_addr();
	int rc;

	if (!i2c_initialized())
		return -1;

	if (i2c_addr == 0) {
		printf("Unsupported bus (%d)\n", i2c_get_bus_num());
		return -1;
	}

	if (len > 255) {
		printf("Unsuppoted transfer length (max 255)\n");
		return -1;
	}

	if (alen > 0) {
		uchar abuf[4];
		i2c_addr_to_buf(addr, alen, abuf);
		rc =  i2c_write_bytes(i2c_addr, chip, abuf, alen, buffer, len);
	} else {
		rc = i2c_write_bytes(i2c_addr, chip, NULL, 0, buffer, len);
	}

	i2c_stop(i2c_addr);

	return rc;
}

/*
 * i2c_probe
 */
int
i2c_probe(uchar chip)
{
	void *i2c_addr = i2c_base_addr();
	int rc;
	uchar dummy;


	if (!i2c_initialized())
		return -1;

	rc = i2c_read_bytes(i2c_addr, chip, &dummy, 1);
	i2c_stop(i2c_addr);

	return rc;
}

/*
  ------------------------------------------------------------------------------
  i2c_init
*/

void
i2c_init(int speed, int slave)
{
	void *i2c_addr = i2c_base_addr();

	if (NULL == i2c_addr) {
		debug("%s:%d - I2C Address is NULL!\n", __FILE__, __LINE__);

		return;
	}

	debug("%s:%d - speed=%d slave=%#x\n", __FILE__, __LINE__, speed, slave);

	/* Enable Master Mode */
	writel(0x1, i2c_addr + AI2C_REG_I2C_X7_GLOBAL_CONTROL);

	i2c_set_bus_speed(speed);
	initialized |= ( 1 << current_bus);
}

/*
 * i2c_set_bus_speed
 */
int
i2c_set_bus_speed(unsigned int speed)
{
	void *i2c_addr = i2c_base_addr();
	unsigned per_clock;
	unsigned clk_mhz;
	unsigned divisor;
	unsigned t_high, t_low, t_setup;

	current_speed = speed;

	if (acp_clock_get(clock_peripheral, &per_clock) < 0) {
		printf("Failed to retreive peripheral clock speed\n");
		return -1;
	}

	divisor = per_clock / (speed/1000);

	clk_mhz = per_clock / 1000;

	debug("i2c_set_bus_speed: per_clk=%uMHz -> ratio=1:%u\n",
	      clk_mhz, divisor);

	if (speed <= 100000) {
		/* Standard mode SCL 50/50, tSU:DAT = 250 ns */
		t_high  = divisor*1/2;
		t_low   = divisor*1/2;
		t_setup = ns_to_clk(250, clk_mhz);
	} else {
		/* Fast mode SCL 33/66, tSU:DAT = 100 ns */
		t_high  = divisor*1/3;
		t_low   = divisor*2/3;
		t_setup = ns_to_clk(100, clk_mhz);
	}

	/* SCL High Time */
	writel(t_high, i2c_addr + AI2C_REG_I2C_X7_SCL_HIGH_PERIOD);
	/* SCL Low Time */
	writel(t_low, i2c_addr + AI2C_REG_I2C_X7_SCL_LOW_PERIOD);
	/* SDA Setup Time */
	writel(t_setup, i2c_addr + AI2C_REG_I2C_X7_SDA_SETUP_TIME);
	/* SDA Hold Time, 5ns */
	writel(ns_to_clk(5, clk_mhz),
	       i2c_addr + AI2C_REG_I2C_X7_SDA_HOLD_TIME);
	/* Filter > 50ns spikes */
	writel(ns_to_clk(50, clk_mhz), i2c_addr + AI2C_REG_I2C_X7_SPIKE_FLTR_LEN);

	/* Configure Time-Out Registers. Find a prescaler value that make the
	 * timeout value fit into the 15-bit counter register.
	 */
	{
		unsigned int tmo_clk = ns_to_clk(SCL_LOW_TIMEOUT, clk_mhz);
		unsigned int prescale = 0;/* log2 of the prescale divider */

		while (tmo_clk > 0x7fff && prescale < 15) {
			++prescale;
			tmo_clk >>= 1;
		}

		if (tmo_clk > 0x7fff)
			tmo_clk = 0x7fff;

		debug("i2c: tmo_clk %u, divider %u\n", tmo_clk, 1<<prescale);
		writel(prescale, i2c_addr + AI2C_REG_I2C_X7_TIMER_CLOCK_DIV);
		writel((1<<15) | tmo_clk,
		       i2c_addr + AI2C_REG_I2C_X7_WAIT_TIMER_CONTROL);
	}

	debug("i2c: SDA_SETUP:        %08x\n",
	      readl(i2c_addr+AI2C_REG_I2C_X7_SDA_SETUP_TIME));
	debug("i2c: SDA_HOLD:         %08x\n",
	      readl(i2c_addr+AI2C_REG_I2C_X7_SDA_HOLD_TIME));
	debug("i2c: SPIKE_FILTER_LEN: %08x\n",
	      readl(i2c_addr+AI2C_REG_I2C_X7_SPIKE_FLTR_LEN));
	debug("i2c: TIMER_DIV:        %08x\n",
	      readl(i2c_addr+AI2C_REG_I2C_X7_TIMER_CLOCK_DIV));
	debug("i2c: WAIT_TIMER:       %08x\n",
	      readl(i2c_addr+AI2C_REG_I2C_X7_WAIT_TIMER_CONTROL));

	return 0;
}

#if defined(CONFIG_I2C_MULTI_BUS)

int
i2c_set_bus_num(unsigned int bus)
{
	if (bus >= CONFIG_SYS_MAX_I2C_BUS) {
		debug("%s:%d - bus, %u, is out of range!\n",
		      __FILE__, __LINE__, bus);

		return -1;
	}

	current_bus = bus;
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);

	return 0;
}

/*
  ------------------------------------------------------------------------------
  i2c_get_bus_num
*/

unsigned int
i2c_get_bus_num(void)
{
	debug("%s:%d - current_bus=%u\n", __FILE__, __LINE__, current_bus);

	return current_bus;
}

#endif	/* CONFIG_I2C_MULTI_BUS */
