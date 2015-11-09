/*
 *  drivers/i2c/axm_i2c.c
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

/*
 * i2c_base_addr - Return the I2C controller base address for currently
 * selected bus.
 */
static unsigned long
i2c_base_addr(void)
{
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = I2C0;
#else
	unsigned long i2c_addr = I2C0;
#endif

#ifdef CONFIG_I2C_MULTI_BUS
	switch (i2c_get_bus_num()) {
	case 0:
		i2c_addr = I2C0;
		break;
	case 1:
		i2c_addr = I2C1;
		break;
#ifndef CONFIG_AXXIA_25xx
	case 2:
		i2c_addr = I2C2;
		break;
	case 3:
		i2c_addr = I2C3;
		break;
#endif
#ifdef CONFIG_AXXIA_XLF_SIM
	case 4:
		i2c_addr = I2C4;
		break;
	case 5:
		i2c_addr = I2C5;
		break;
	case 6:
		i2c_addr = I2C6;
		break;
	case 7:
		i2c_addr = I2C7;
		break;
	case 8:
		i2c_addr = I2C8;
		break;
	case 9:
		i2c_addr = I2C9;
		break;
	case 10:
		i2c_addr = I2C10;
		break;
	case 11:
		i2c_addr = I2C11;
		break;
#endif
	default:
		return 0;
	}
#endif

	return i2c_addr;
}

static int
i2c_initialized(void)
{
	if (!(initialized & (1<<current_bus))) {
		printf("I2C dev %d not initialized\n", current_bus);
		return 0;
	}
	return 1;
}

/*
 * i2c_check_status - Check status of the current transfer.
 * Return -1 on transfer error.
 */
static int
i2c_check_status(unsigned int status, unsigned int *acc_status)
{
	if (status & MST_STATUS_ERR) {
		debug("i2c: transfer ABORTED (status %#x/%#x)\n", status, *acc_status);
		return -1;
	}
	if (status & MST_STATUS_SNS)
		*acc_status |= MST_STATUS_SNS;
	if (status & MST_STATUS_SCC)
		*acc_status |= MST_STATUS_SCC;
	return 0;
}

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
 * i2c_write_bytes - Perform single I2C write.
 *
 * <START> <chip_addr R/nW=0> <addr[0]> ... <addr[len-1]> <data[0]> <data[1]>
 * ... <data[len-1]>
 */
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
int
i2c_write_bytes(unsigned long long i2c_addr, uchar chip,
		const uchar *addr, int alen,
		const uchar *data, int dlen)
#else
int
i2c_write_bytes(unsigned long i2c_addr, uchar chip,
		const uchar *addr, int alen,
		const uchar *data, int dlen)
#endif
{
	int result = 0;
	int len = alen + dlen;
	unsigned int status;
	unsigned int acc_status = 0;/* Accumulated status bits
				     * to determine when transfer
				     *is complete */
	unsigned int done_bits = MST_STATUS_SNS;

	debug("_i2c_write: chip=%#x, addr=[%02x %02x] alen=%d buffer=[%02x %02x %02x %02x], len=%d\n",
	      chip, addr[0], addr[1], alen, data[0], data[1], data[2], data[3], len);

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
				unsigned txbyte = 0;
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
			break;
	}
	/* Wait for state machine to go IDLE */
	while (readl(i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND) & 0x8)
		;

	debug("i2c_write: transfer finished, xfr_rx=%u/%u xfr_tx=%u/%u\n",
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_BYTES_XFRD),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER),
	      readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD));

	return result;
}

/*
 * i2c_read_bytes - Performs a single I2C read.
 *
 * <START> <chip_addr R/nW=1> <buffer[0]> <buffer[1]> ... <buffer[len-1]>
 */
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
int
i2c_read_bytes(unsigned long long i2c_addr, uchar chip, uchar *buffer, int len)
#else
int
i2c_read_bytes(unsigned long i2c_addr, uchar chip, uchar *buffer, int len)
#endif
{
	int result = 0;
	unsigned int status;
	unsigned int acc_status = 0;/* Accumulated status bits
				     * to determine when transfer
				     * is complete */
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
 * i2c_stop - Generate STOP on the I2C bus to terminate a transaction.
 */
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
int
i2c_stop(unsigned long long i2c_addr)
#else
int
i2c_stop(unsigned long i2c_addr)
#endif
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
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = i2c_base_addr();
#else
	unsigned long i2c_addr = i2c_base_addr();
#endif
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
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = i2c_base_addr();
#else
	unsigned long i2c_addr = i2c_base_addr();
#endif
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
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = i2c_base_addr();
#else
	unsigned long i2c_addr = i2c_base_addr();
#endif
	int rc;
	uchar dummy;


	if (!i2c_initialized())
		return -1;

	rc = i2c_read_bytes(i2c_addr, chip, &dummy, 1);
	i2c_stop(i2c_addr);

	return rc;
}

/*
 * i2c_init
 */
void
i2c_init(int speed, int slave)
{
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = i2c_base_addr();
#else
	unsigned long i2c_addr = i2c_base_addr();
#endif

	debug("i2c_init: speed=%d slave=%#x\n", speed, slave);

	/* Enable Master Mode */
	writel(0x1, i2c_addr + AI2C_REG_I2C_X7_GLOBAL_CONTROL);

	i2c_set_bus_speed(speed);

	initialized |= (1<<current_bus);
}

/*
 * i2c_set_bus_speed
 */
int
i2c_set_bus_speed(unsigned int speed)
{
#if defined(CONFIG_AXXIA_56XX_SIM) || defined(CONFIG_AXXIA_XLF_SIM)
	unsigned long long i2c_addr = i2c_base_addr();
#else
	unsigned i2c_addr = i2c_base_addr();
#endif
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

#ifdef CONFIG_I2C_MULTI_BUS
int
i2c_set_bus_num(unsigned int bus)
{
	if (bus >= CONFIG_SYS_MAX_I2C_BUS)
		return -1;

	current_bus = bus;
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);

	return 0;
}

unsigned int
i2c_get_bus_num(void)
{
	return current_bus;
}
#endif
