/*
 * sbb.c
 *
 * Interface to the SBB (Secure Boot Block)
 *
 * Copyright (C) 2014 LSI Corporation
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

#include <config.h>
#include <common.h>
#include <watchdog.h>

#include <asm/io.h>

/*
  ==============================================================================
  ==============================================================================
  Local
  ==============================================================================
  ==============================================================================
*/

#define ECM_BASE        (0x80000000 + 0x10031800)
#define ECM_CTRL_REG    (ECM_BASE + 0x00)
#define ECM_STAT_REG    (ECM_BASE + 0x04)
#define ECM_ADDR_REG    (ECM_BASE + 0x14)
#define ECM_RDAT_REG    (ECM_BASE + 0x40)

#define SBB_BASE        (0x80000000 + 0x10160000)


/*
  ------------------------------------------------------------------------------
  read_ecm
*/

static int
read_ecm(int bit_address, int number_of_bits, int pe_means_zero,
	 unsigned long *destination)
{
	unsigned long value;
	int i;

	/*
	  Verify that ReadEFuse is 0 (bit 0 of the control register).
	*/

	value = readl(ECM_CTRL_REG);

	if (0 != (value & 1)) {
		printf("ECM Read Error: ReadEFuse is not 0.\n");
		return -1;
	}

	/*
	  Set ClearReadData and PwrDown.  Clear PadEnb.
	*/

	writel(0x8080, ECM_CTRL_REG);

	/*
	  Set ReadAddr 12:0 to the starting bit address.
	*/

	value = readl(ECM_ADDR_REG);
	value &= ~0x1fff;
	value |= (bit_address & 0x1fff);
	writel(value, ECM_ADDR_REG);

	/*
	  Clear PwrDown and PadEnb.
	*/

	writel(0, ECM_CTRL_REG);

	/*
	  Wait at least 900 ns.
	*/

	udelay(1);

	/*
	  Clear the status bits.
	*/

	writel(0x1fbc0000, ECM_STAT_REG);

	/*
	  Update ReadDataSize (number of bits to read).  Clear PwrDown and
	  PadEnb.  Set ReadEFuse.
	*/

	value = readl(ECM_CTRL_REG);
	value &= ~0xff000000;
	value |= (number_of_bits & 0xff) << 24;
	value &= ~(1 << 7);
	value &= ~(1 << 6);
	value |= 1;
	writel(value, ECM_CTRL_REG);

	/*
	  Wait for LocalReadDone to be set.
	*/

	while (0 == (readl(ECM_STAT_REG) & 0x20000000)) {
		udelay(1);
	}

	/*
	  Set PwrDown and clear PadEnb.
	*/

	writel(0x80, ECM_CTRL_REG);

	/*
	  Clear LocalReadDone.
	*/

	writel(0x20000000, ECM_STAT_REG);

	/*
	  Check the status.
	*/

	value = (0x1fbc0000 & readl(ECM_STAT_REG));

	if (0 != value) {
		printf("ECM Read Error: Status is 0x%08lx.\n", value);
		return -2;
	} else {
		/*
		  Read Values.
		*/

		for (i = 0; i <= (number_of_bits / 32); ++i)
        {
			if (3 == number_of_bits)
				*destination++ =
					readl(ECM_RDAT_REG + (0x4 * i));
			else
				*destination++ =
					swab32(readl(ECM_RDAT_REG + (0x4 * i)));
        }
	}

	return 0;
}

/*
  ------------------------------------------------------------------------------
  print_sbb_efuse
*/

#undef PRINT_SBB_EFUSE
/*#define PRINT_SBB_EFUSE*/
#ifdef PRINT_SBB_EFUSE
static int
print_sbb_efuse(char *label, int bit_address, int number_of_bits)
{
	unsigned long fuses[8];
    int i;

	memset((void *)fuses, 0, sizeof(unsigned long) * 8);

	if (0 != read_ecm(bit_address, number_of_bits, 0, (void *)fuses)) {
		printf("print_sbb_efuse():read_ecm() failed!\n");
		return -1;
	}

	printf("%s:\n\t", label);
	for (i = 0; i <= (number_of_bits/32); ++i) {
		printf("%08lx", fuses[i]);
	}
	puts("\n");

	return 0;
}
#endif	/* PRINT_SBB_EFUSE */

/*
  ------------------------------------------------------------------------------
  lock_sbb
*/

static int
lock_sbb(void)
{
	unsigned long value;

	value = readl(SBB_BASE + 0x800);

	if (0 == value)
		return -1;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  unlock_sbb
*/

static void
unlock_sbb(void)
{
	writel(0xffffffff, (SBB_BASE + 0x800));
}

static int
report_errors(unsigned long sbb_interrupt_status, int verbose)
{
	int rc = 0;

	/*
	  In all other cases, display the error string(s).
	*/

	if (0 != (sbb_interrupt_status & 0x4)) {
		if (0 != verbose)
			printf("SBB Error: HW Error\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x8)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Key Encryption Key\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x10)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Storage Root Key\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x20)) {
		if (0 != verbose)
			printf("SBB Error: Secure Boot is Disabled\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x40)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Function\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x80)) {
		if (0 != verbose)
			printf("SBB Error: Invalid ID\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x100)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Length\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x200)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Padding\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x400)) {
		if (0 != verbose)
			printf("SBB Error: Unaligned Data\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x800)) {
		if (0 != verbose)
			printf("SBB Error: SDO Authentication Fails\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x1000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Boot Image\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x2000)) {
		if (0 != verbose)
			printf("SBB Error: ECDSA Initialization Failed\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x4000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Version Number\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x8000)) {
		if (0 != verbose)
			printf("SBB Error: Unaligned Address\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x20000)) {
		if (0 != verbose)
			printf("SBB Error: Self-Test Failed\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x40000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Customer Key #1\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x80000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Customer Key #2\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x100000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Crypto Mode\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x200000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Key\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x400000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Hash Length\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x800000)) {
		if (0 != verbose)
			printf("SBB Error: Invalid Public Key Authentication Key\n");

		rc = -1;
	}

	if (0 != (sbb_interrupt_status & 0x1000000)) {
		if (0 != verbose)
			printf("SBB Error: Signature Generation Timeout\n");

		rc = -1;
	}

	return rc;
}

/*
  ------------------------------------------------------------------------------
  run_sbb_function
*/

#define SBB_LOCKUP_WA

static int
run_sbb_function(int function, size_t image_length,
		 unsigned long *parameters, int number_of_parameters,
		 int verbose)
{
	int i;
	unsigned long value;
	int sbb_enabled;
	ncp_uint32_t cycles_per_ms;
	unsigned long long cycles;
	int retries;
#ifdef SBB_LOCKUP_WA
	unsigned long aux_ctl;
#endif

	if (-1 == acp_clock_get(clock_system, &cycles_per_ms)) {
		printf("Unable to get the system frequency!\n");

		return -1;
	}

	/*
	  Max cycles required by the SBB.

	  2 * 10^6 + (image_size_in_bits / 128 * 25) + C clock cycles.

	  Where C is less than 10^6.
	*/

	cycles = 3000000ULL + ((image_length / 16)  * 25);
	retries = cycles / cycles_per_ms; /* Estimated time. */

	/* Make sure SBB is enabled (check the fuses). */
	sbb_enabled = is_sbb_enabled(verbose);
	if (-1 == sbb_enabled || 0 == sbb_enabled)
		return -1;

	/* Get the semaphore. */
	if (0 != lock_sbb())
		return -1;

	/* Write the input parameters. */
	for (i = 0; i < number_of_parameters; ++i) {
		writel(parameters[i], (SBB_BASE + 0x838 + (i * 4)));
	}

	/* Clear the interrupt status registers. */
	writel(0xffffffff, (SBB_BASE + 0xc04));

#ifdef SBB_LOCKUP_WA
	aux_ctl = readl(DICKENS + (0x86 << 16) + 0x500);
	writel(0x9, (DICKENS + (0x86 << 16) + 0x500));
#endif

	/* Write the function. */
	writel(function, (SBB_BASE + 0x804));

	if (function != readl(SBB_BASE + 0x804))
		return -1;

	/* Wait for the "done" bit. */
	value = readl(SBB_BASE + 0xc04);

	while (0 == (value & 1)) {
		udelay(1000);

		if (0 < retries--) {
			WATCHDOG_RESET();
		} else {
#ifdef SBB_LOCKUP_WA
			writel(aux_ctl, (DICKENS + (0x86 << 16) + 0x500));
#endif
			printf("Timed out waiting for SBB Done Bit\n");
			acp_failure(__FILE__, __func__, __LINE__);
		}

		value = readl(SBB_BASE + 0xc04);
	}

#ifdef SBB_LOCKUP_WA
	writel(aux_ctl, (DICKENS + (0x86 << 16) + 0x500));
#endif

	/* Release the semaphore. */
	unlock_sbb();

	/* Check for errors. */
	if (0 != report_errors(value, verbose))
		return -1;

	return 0;
}

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  is_sbb_enabled

  Returns 1 if enabled, 0 if not, -1 if errror.
*/

int
is_sbb_enabled(int verbose)
{
	unsigned long fuses[8];
	ncp_uint32_t  value;

	/* Check Force Fuse */
	ncr_read32(NCP_REGION_ID(0x156, 0), 0x1064, &value);

	if (0 != (value & 0x800000)) {

		if (0 != verbose)
			printf("Secure Boot Enabled (Force Fuse)\n");

		return 1;
	}

	/* Secure Boot Enable Bit. */
	memset((void *)fuses, 0, sizeof(unsigned long) * 8);

	if (0 != read_ecm(0x18, 0x3, 0, (void *)fuses)) {
		printf("read_ecm() failed!\n");

		return -1;
	}

	if (0 == (fuses[0] & 0x8)) {
		if (0 != verbose)
			printf("Secure Boot Disabled\n");

		return 0;
	}

	if (0 != verbose)
		printf("Secure Boot Enabled\n");

	return 1;
}

/*
  ------------------------------------------------------------------------------
  sbb_image_max_length
*/

int
sbb_image_max_length(void *image, size_t *length)
{
	unsigned long *sbb_header;

	/*
	  The size of the contents of a signed/encrypted image
	  can be calculated as follows.

	  ImageSectionLength - Pad

	  ImageSectionLength is the second word, and Pad is
	  the byte after that.

	  The full size of the signed/encrypted image is not
	  available, but will be less than 259 bytes more than
	  the contents.
	*/

	sbb_header = (unsigned long *)image;
	*length = 0;

	if (0x53424211 != ntohl(sbb_header[0]))
		return -1;

	*length = ntohl(sbb_header[1]) -
		((ntohl(sbb_header[2]) & 0xff000000) >> 24) +
		259;

	return 0;
}

/*
  ------------------------------------------------------------------------------
  sbb_verify_image
*/

int
sbb_verify_image(void *source, void *destination, size_t max_length,
		 int safe, int invalidate, int verbose)
{
	unsigned long parameters[4];
	int sbb_enabled;

	/* If SBB is disabled, return success */
	sbb_enabled = is_sbb_enabled(verbose);

	if (1 != sbb_enabled)
		return sbb_enabled;

#ifdef PRINT_SBB_EFUSE
	/* KAKPubQx Copy 0 */
	print_sbb_efuse("Public Key Authentication Key Qx (Copy 0)",
			0x88, 0xff);
	/* KAKPubQy Copy 0 */
	print_sbb_efuse("Public Key Authentication Key Qy (Copy 0)",
			0x228, 0xff);
	/* SBKEK SHA2 Copy 0*/
	print_sbb_efuse("Secret Secure Boot Key SHA2 (Copy 0)",
			0x6b8, 0x7f);
#endif	/* PRINT_SBB_EFUSE */

	/* Set up the parameters. */
	parameters[0] = 0;
	parameters[1] = (unsigned long)source;
	parameters[2] = 0;
	parameters[3] = (unsigned long)destination;

	/* Run the function. */
	if (0 != run_sbb_function((0 == safe) ? 1 : 11, max_length,
				  parameters, 4, verbose)) {
		if (0 != invalidate)
			memset((void *)destination, 0, 16);

		return -1;
	}

	if (0 != verbose)
		printf("SBB: Image Verification Successful\n");

	return 0;
}
