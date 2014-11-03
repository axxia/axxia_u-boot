#include <common.h>
#include <spi.h>
#include <asm/io.h>

#define SPI_NUM_CS 5

int
spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	int valid = bus == 0 && cs < SPI_NUM_CS;
	return valid;
}

void
spi_cs_activate(struct spi_slave *slave)
{
	writel((0x1f & ~(1<<slave->cs)), (unsigned long *)(SSP + SSP_CSR));
}

void
spi_cs_deactivate(struct spi_slave *slave)
{
	writel(0x1f, (unsigned long *)(SSP + SSP_CSR));
}

unsigned int
spi_get_per_clk(void)
{
	unsigned per_clk;

	if (0 != acp_clock_get(clock_peripheral, &per_clk))
		per_clk = CLK_REF0;
	else
		per_clk *= 1000;

	return per_clk;
}
