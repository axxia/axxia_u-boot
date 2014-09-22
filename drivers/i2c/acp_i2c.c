/*
 *  drivers/i2c/axxia_i2c.c
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

#include <common.h>
#include <asm/io.h>
#include <i2c.h>

/*
  ==============================================================================
  ==============================================================================
  Local
  ==============================================================================
  ==============================================================================
*/
#ifndef CONFIG_AXXIA_ARM
#define I2C_STATUS_READ_DELAY 10000
#define I2C_MAX_TX_RETRIES 20
#define I2C_SINGLE_WRITE_SIZE 7
#else
/*! @def AI2C_I2CPROT_MAX_XFR_SIZE
    @brief Maximum number of bytes that may be moved at one time over the
        I2C bus.
*/
#define AI2C_I2CPROT_MAX_XFR_SIZE           8

/*! @def AI2C_I2CPROT_MAX_BUF_SIZE
    @brief Maximum number of bytes that may be stored at one time over
        the I2C bus i.e. size of TXD0+TXD1.
*/
#define AI2C_I2CPROT_MAX_BUF_SIZE           8

/* Max number of tries at looking for an I/O success */
#define AI2C_I2C_CHECK_COUNT                            0xFFFFF
#define TRUE	1
#define FALSE   0
#endif

static unsigned long bus_speed = 1;
static int initialized = -1;
static int i2c_bus_num = -1;
static unsigned long mcc_value = 1;

/*
  ==============================================================================
  ==============================================================================
  Global
  ==============================================================================
  ==============================================================================
*/

/*
  ==============================================================================
  ==============================================================================
  U-Boot Interface
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  i2c_read
*/

int
i2c_read(uchar chip, uint address, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr;
	unsigned int bus_num;

	if (0 == initialized)
		return -1;

	if (0 == alen) {
		printf("Unsupported address length!  "
		       "Only .1 and .2 are supported.\n");
		return -1;
	}

	i2c_addr = I2C0;
#ifdef CONFIG_I2C_MULTI_BUS
	bus_num = i2c_get_bus_num();
	switch (bus_num) {
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
		default:
#ifndef CONFIG_AXXIA_25xx
                printf("Unsupported bus num = %d, only 0, 1, 2 and 3 are supported\n", bus_num);
#else
                printf("Unsupported bus num = %d, only 0 and 1 are supported\n", bus_num);

#endif
                return -1;
	}
#endif


#ifndef CONFIG_AXXIA_ARM
	DEBUG_PRINT("chip=0x%x/%d addr=%u alen=%d len=%d\n",
		    chip, chip, address, alen, len);

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

                WRITEL(address, i2c_addr + I2C_TXD0);
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
                address += this_len;
        }
#else
	while (0 < len) {
		unsigned long status, numInFifo;
		unsigned long value[2], endit, deadman;
		uchar input[8];
		int this_len, count;
		int retries, i;
		int stop;

		if (8 <= len) {
			this_len = 8;
			stop = 0;
		} else  {
			this_len = len;
			stop = 1;
		}

		/* Anything available yet? */
		numInFifo = readl(i2c_addr + AI2C_REG_I2C_X7_MST_RX_FIFO); 


		/* Didn't 'fail', but nothing really moved either */
		if ((numInFifo & 0xFF))
			return -1;

		/* # of bytes to move */
		writel(this_len, i2c_addr + AI2C_REG_I2C_X7_MST_RX_XFER);


		/* target slave address */
		if (2 == alen) {
			unsigned long a1 = (0x1e << 3) |
				((((chip|address) >> 8) & 0x3) << 1) |
				0x1;
			unsigned long  a2 = ((chip|address) & 0xff);
			writel(a1, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);
			writel(a2, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_2);
		} else {
			unsigned long a1 = (((chip|address) & 0x7f) << 1) | 0x1;
			unsigned long a2 = 0x00000000;
			writel(a1, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);
			writel(a2, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_2);
		} 
        /* And send it on its way (automatic or manual transfer command) */
		{
			unsigned long   r = 0x8 | ((stop) ? 0x1 : 0x0);
			writel( r, i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND);
		}


		/* Wait for the data to arrive */
		for (endit = FALSE, deadman = 0;
			!endit && (deadman < AI2C_I2C_CHECK_COUNT); deadman++) {
			unsigned long   reg = 0, status; 

			reg = readl(i2c_addr + AI2C_REG_I2C_X7_MST_INT_STATUS);
			if (stop && ((reg >> 10) & 0x1))
				endit = TRUE;
			if (!stop && ((reg >> 11) & 0x1))
				endit = TRUE;
			if (reg & 0x00000078) { /* al || nd || na || ts */
				return -1;
			}
		} 

		if (!endit)
			return -1;

		/* Finally, determine how many bytes were sent successfully */
		numInFifo = readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD);
		count = MIN((numInFifo & 0xff), this_len);

		for (i = 0; i < count; i++) {
			unsigned long v; 
			v = readl(i2c_addr + AI2C_REG_I2C_X7_MST_DATA);
			input[i] = (v & 0xff);
		} 
		
		debug("%s:%d -- input[] = "
				"{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
				__FILE__, __LINE__,
				value[0], value[1], input[0], input[1], input[2], input[3],
				input[4], input[5], input[6], input[7]);
		memcpy(buffer, input, this_len);
		len -= this_len;
		buffer += this_len;
		address += this_len;
	}
#endif

	return 0;
}

/*
  -------------------------------------------------------------------------------
  _i2c_write
*/

static int
_i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned long i2c_addr;
	unsigned int bus_num;
	unsigned int endit, deadman;

	debug("%s:%d -- chip=0x%x/%d addr=%u alen=%d len=%d\n",
			__FILE__, __LINE__,
		    chip, chip, addr, alen, len);
	i2c_addr = I2C0;

#ifdef CONFIG_I2C_MULTI_BUS
	bus_num = i2c_get_bus_num();
	switch (bus_num) {
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
		default:
#ifndef CONFIG_AXXIA_25xx
                printf("Unsupported bus num = %d, only 0, 1, 2 and 3 are supported\n", bus_num);
#else
                printf("Unsupported bus num = %d, only 0 and 1 are supported\n", bus_num);
#endif
                return -1;
	}
#endif

#ifndef CONFIG_AXXIA_ARM

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
			debug("input[%d]=0x%x\n", i, input[i]);
		}

		DEBUG_PRINT("buffer[] = {0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "input[]  = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "value[] = "
			    "{0x%08lx 0x%08lx}\n"
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

#else
	while (0 < len) {
		unsigned long status;
		unsigned long control;
		unsigned long value[2] = {0, 0};
		uchar *input = (uchar *)value;
		int this_len, countRem, countUsed;
		int i;
		int retries;
		unsigned long lTenBitMode;

		if (8 <= len) {
			this_len = 8;
		} else  {
			this_len = len;
		}
		countRem = this_len;

		printf("len=%d this_len=%d addr=%d buffer=0x%p\n",
			    len, this_len, addr, buffer); 

		if ((((chip | addr) & 0x1f) == 0x1e)  || (alen == 2))
			lTenBitMode = TRUE;
		else
			lTenBitMode = FALSE;

		for (countUsed = 0; (len > countUsed);) {
			unsigned long   thisWid = (countRem > 0x8) ? 0x8 : countRem;
			unsigned long   thisXfr = thisWid;
			unsigned long   actWid = 0;
			unsigned char    inOutTxd[AI2C_I2CPROT_MAX_BUF_SIZE];
			unsigned long   k, numInFifo;
			int   stop = 0x1;


			if (thisWid < countRem)
				stop = 0; 

			for (k = 0; k < thisWid; k++)
				input[k] = buffer[countUsed+k];


			debug("%s:%d -- buffer[] = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n"
			    "input[]  = "
			    "{0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x}\n",
			    __FILE__, __LINE__,
			    buffer[0], buffer[1], buffer[2], buffer[3],
			    buffer[4], buffer[5], buffer[6], buffer[7],
			    input[0], input[1], input[2], input[3],
			    input[4], input[5], input[6], input[7]);


			/* Check if previous transfer is still in progress? */
			numInFifo = readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_FIFO);
			
			if ((numInFifo & 0xFF)) {
				/* Didn't 'fail', but nothing really moved either */
				return -1;
			} 

			/* # of bytes to move */
			writel(thisWid, i2c_addr + AI2C_REG_I2C_X7_MST_TX_XFER);


			if (lTenBitMode) {
				unsigned long a1 = (0x1e << 3) | ((((chip | addr) >> 8) & 0x3) << 1) | 0x0;
				unsigned long a2 = ((chip|addr) & 0xff);
				writel(a1, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);
				writel(a2, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_2);
			} else {
				unsigned long a1 = (((chip|addr) & 0x7f) << 1) | 0x0;
				unsigned long a2 = 0x00000000;
				writel(a1, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_1);
				writel(a2, i2c_addr + AI2C_REG_I2C_X7_MST_ADDR_2);
			}

			/* Queue up the data */
			for (i = 0; i < thisWid; i++) {
				unsigned long v = buffer[i];
				writel(v, i2c_addr + AI2C_REG_I2C_X7_MST_DATA);
			}

			/* And send it on its way (automatic or manual transfer command) */
			{
				unsigned long   r = 0x8 |((stop) ? 0x1 : 0x0);
				writel(r, i2c_addr + AI2C_REG_I2C_X7_MST_COMMAND);
			}

			/* Wait for the data to arrive */
			for (endit = FALSE, deadman = 0;
				!endit && (deadman < AI2C_I2C_CHECK_COUNT); deadman++) {
				unsigned long   reg = 0;
				reg = readl(i2c_addr + AI2C_REG_I2C_X7_MST_INT_STATUS);
			
				if (stop && ((reg >> 10) & 0x1))  /* auto xfer; ss */
					endit = TRUE;
				if (!stop && ((reg >> 11) & 0x1)) /* man xfer; sns */
					endit = TRUE;
				if (reg & 0x00000078) {           /* al || nd || na || ts */
					return -1;
				}
			}

			if (!endit) {
				/* Timed out */
				return -1;
			}

			/* Finally, determine how many bytes were sent successfully */
			numInFifo = readl(i2c_addr + AI2C_REG_I2C_X7_MST_TX_BYTES_XFRD);

			--this_len;
			len -= this_len;
			addr += this_len;
		}
	}
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

/*
  ------------------------------------------------------------------------------
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
  ------------------------------------------------------------------------------
  i2c_init
*/

void
i2c_init(int speed, int slave)
{
#ifndef CONFIG_AXXIA_ARM

        i2c_set_bus_speed(speed);
        initialized = 1;

        return;
#else
	unsigned long i2c_addr;
	unsigned int bus_num;
	unsigned long per_clock;
	unsigned long clockMhz;
    unsigned long timerLoad;


	i2c_addr = I2C0;

#ifdef CONFIG_I2C_MULTI_BUS
	bus_num = i2c_get_bus_num();
	switch (bus_num) {
		case 0:
			i2c_addr = I2C0;
			break;
		case 1:
			i2c_addr = I2C1;
			break;
		case 2:
			i2c_addr = I2C2;
			break;
		case 3:
			i2c_addr = I2C3;
			break;
		default:
                printf("Unsupport bus num = %d, only 0, 1, 2 and 3 are supported\n", bus_num);
                return;
	}
#endif

	  /* Enable Master Mode */
	writel(0x1, i2c_addr + AI2C_REG_I2C_X7_GLOBAL_CONTROL);

	/* Configure Clock setup registers */
	/*   Assume PCLK=50MHZ, I2C=Fast mode (400KHz) */

	do {
		for (;;) {
			int rc;
			rc = acp_clock_get(clock_system, &per_clock);

			if (0 == rc) {
				clockMhz = per_clock/(1024*1024);
				break;
			}
		}
	} while (0 == per_clock);

	/* SCL High Time: 1.4 us - 1 PCLK */
	timerLoad = (clockMhz / 4) - 1;

	writel(timerLoad, i2c_addr + AI2C_REG_I2C_X7_SCL_HIGH_PERIOD); 

	/* SCL Low Time: 1.1 us - 1 PCLK */
	timerLoad = (clockMhz / 5) - 1;
	writel(0x0, i2c_addr + AI2C_REG_I2C_X7_SCL_LOW_PERIOD); 

	/* SDA Setup Time: SDA setup=600ns with margin */
	writel(0x0000001E, i2c_addr + AI2C_REG_I2C_X7_SDA_SETUP_TIME);

	/* SDA Hold Time: SDA setup=500ns with margin */
	writel(0x00000019, i2c_addr + AI2C_REG_I2C_X7_SDA_HOLD_TIME); 

	/* Filter > 50ns spikes */
	writel(0x00000003, i2c_addr + AI2C_REG_I2C_X7_SPIKE_FLTR_LEN); 

	/* Configure Time-Out Registers */
	/* Every 10.24ux = 512 x 20ns */
	writel(0x00000003, i2c_addr + AI2C_REG_I2C_X7_TIMER_CLOCK_DIV); 

	/* Desired Time-Out = 25ms */
	writel(0x00008989, i2c_addr + AI2C_REG_I2C_X7_WAIT_TIMER_CONTROL);

	return;
#endif
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

#ifndef CONFIG_AXXIA_ARM
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
	debug("per_clock=%lu divisor=%lu mcc_value=0x%x bus_speed=%lu\n",
		    per_clock, divisor, mcc_value, bus_speed);


	return 0;
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
	if (i2c_bus_num == -1) {
		i2c_bus_num = 0;
	}
	return i2c_bus_num;
}
#endif
