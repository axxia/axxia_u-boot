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
  ===============================================================================
  ===============================================================================
  Local
  ===============================================================================
  ===============================================================================
*/

#define SWAP32(value) ((((value) & 0x000000ff) << 24) | \
                      (((value) & 0x0000ff00) <<  8)  | \
                      (((value) & 0x00ff0000) >>  8)  | \
                      (((value) & 0xff000000) >> 24))

#define I2C_STATUS_READ_DELAY 10000
#define I2C_MAX_TX_RETRIES 20
#define I2C_SINGLE_WRITE_SIZE 7

static unsigned long bus_speed;
static unsigned long mcc_value;
static int initialized = 0;

/*
  -------------------------------------------------------------------------------
  _i2c_write
*/

static int
_i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
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
			WRITEL(0x20000580, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000500, I2C0 + I2C_MTC);

		/* constants for clocks... */
		WRITEL(mcc_value, I2C0 + I2C_MCC);
		WRITEL(0x00800000, I2C0 + I2C_MSTSHC);
		WRITEL(0x00000080, I2C0 + I2C_MSPSHC);
		WRITEL(0x00140014, I2C0 + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			WRITEL(0x20000100, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000180, I2C0 + I2C_MTC);

		WRITEL(chip, I2C0 + I2C_MSLVADDR);

		memset(input, 0, sizeof(input));
		DEBUG_PRINT("buffer[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "input[]  = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
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

		DEBUG_PRINT("buffer[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "input[]  = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "value[] = "
			    "{0x%08lx 0x%08lx}\n"
			    buffer[0], buffer[1], buffer[2], buffer[3],
			    buffer[4], buffer[5], buffer[6], buffer[7],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7],
			    value[0], value[1]);
		WRITEL(value[1], I2C0 + I2C_TXD0);
		WRITEL(value[0], I2C0 + I2C_TXD1);

		/* stop, mma, this_len bytes, tr */
		if (2 == alen)
			control = 0x20000181 | (this_len << 1);
		else
			control = 0x20000101 | (this_len << 1);

		WRITEL(control, I2C0 + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(I2C0 + I2C_MTS);
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
	i2c_set_bus_speed(speed);
	initialized = 1;

	return;
}

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

	load_value = 49;

	WRITEL(0, (TIMER1 + TIMER_CONTROL));
	WRITEL(load_value, (TIMER1 + TIMER_LOAD));
	WRITEL(load_value, (TIMER1 + TIMER_VALUE));
	WRITEL(0xc0, (TIMER1 + TIMER_CONTROL));

#ifdef ACP_25xx
        printf("setting TIMER0\n");
        WRITEL(0, (TIMER0 + TIMER_CONTROL));
        WRITEL(load_value, (TIMER0 + TIMER_LOAD));
        WRITEL(load_value, (TIMER0 + TIMER_VALUE));
        WRITEL(0xc0, (TIMER0 + TIMER_CONTROL));
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

/*
  -------------------------------------------------------------------------------
  i2c_probe
*/

int
i2c_probe(uchar chip)
{
	uchar buffer[8];
	int rc;

	if (0 == initialized)
		return -1;

	memset(buffer, 0, sizeof(buffer));
	rc = i2c_read(chip, 0, 1, buffer, 4);

	if (0 == rc)
		return 0;

	return -1;
}

/*
  -------------------------------------------------------------------------------
  i2c_read
*/

int
i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	if (0 == initialized)
		return -1;

	if (0 == alen) {
		printf("Unsupported address length!  "
		       "Only .1 and .2 are supported.\n");
		return -1;
	}

	DEBUG_PRINT("chip=0x%x/%d addr=%u alen=%d len=%d\n",
		    chip, chip, addr, alen, len);

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
			WRITEL(0x20000580, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000500, I2C0 + I2C_MTC);

		/* constants for clocks... */
		WRITEL(mcc_value, I2C0 + I2C_MCC);
		WRITEL(0x00800000, I2C0 + I2C_MSTSHC);
		WRITEL(0x00000080, I2C0 + I2C_MSPSHC);
		WRITEL(0x00140014, I2C0 + I2C_MDSHC);

		/* stop, mma */
		if (2 == alen)
			WRITEL(0x20000180, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000100, I2C0 + I2C_MTC);

		WRITEL(chip, I2C0 + I2C_MSLVADDR);

		WRITEL(addr, I2C0 + I2C_TXD0);
		WRITEL(0x00000000, I2C0 + I2C_TXD1);

		/* stop, mma, one byte, tr */
		if (2 == alen)
			WRITEL(0x20000183, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000103, I2C0 + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		retries = I2C_MAX_TX_RETRIES;

		do {
			/*
			  TODO: Why is this delay needed?
			*/
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(I2C0 + I2C_MTS);
			--retries;
		} while ((0 == status) && (0 < retries));

		if ((1 != status) || (0 == retries))
			return -1;

		if (2 == alen)
			WRITEL(0x20000580, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000500, I2C0 + I2C_MTC);

		WRITEL(mcc_value, I2C0 + I2C_MCC);
		WRITEL(0x00800000, I2C0 + I2C_MSTSHC);
		WRITEL(0x00000080, I2C0 + I2C_MSPSHC);
		WRITEL(0x00140014, I2C0 + I2C_MDSHC);
		WRITEL(0x00000000, I2C0 + I2C_MIE);

		if (2 == alen)
			WRITEL(0x20000180, I2C0 + I2C_MTC);
		else
			WRITEL(0x20000100, I2C0 + I2C_MTC);

		WRITEL(chip, I2C0 + I2C_MSLVADDR);
		WRITEL((this_len << 1) | 1, I2C0 + I2C_MRC);
		WRITEL(0x20000301, I2C0 + I2C_MTC);

		/* wait for completion and verify that te is clear. */
		do {
			udelay(I2C_STATUS_READ_DELAY);
			status = READL(I2C0 + I2C_MRS);
		} while (1 != (status & 1));

		if (1 != (status & 0x3))
			return -1;

		value[1] = READL(I2C0 + I2C_RXD0);
		value[0] = READL(I2C0 + I2C_RXD1);
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

	if (0 == initialized)
		return -1;

	while (CHUNK_SIZE < len) {
		rc = _i2c_write(chip, addr, alen, buffer, CHUNK_SIZE);

		if (0 != rc)
			return rc;

		addr += CHUNK_SIZE;
		buffer += CHUNK_SIZE;
		len -= CHUNK_SIZE;
	}

	return _i2c_write(chip, addr, alen, buffer, len);
}
