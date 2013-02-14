/*
 * common/cmd_lsi_test.c
 *
 * (C) Copyright 2010
 * LSI, john.jacques@lsi.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#define LSI_DEBUG
#define LSI_LOGIO
#include <config.h>

#ifdef CONFIG_ACP

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <nand.h>

/*
  ======================================================================
  Local Stuff
  ======================================================================
*/

static int
test_pipe_display(unsigned long region, unsigned long value,
		  int link, int extras, unsigned long *extra_offset)
{
	int i;
	int j;
	unsigned long *offset;
	unsigned long temp[3];

	i = 0;
	j = extras;
	offset = extra_offset;

	while (0 < j--) {
		if (0 != ncr_read32(region, *offset++, &(temp[i++])))
			goto pipe_display_read_failed;
	}

	i = 0;
	j = extras;
	offset = extra_offset;

	printf("0x11f.2.0x%08lx contains 0x%08lx\n",
	       link, value);

	while (0 < j--) {
		printf("0x115.2.0x%08lx contains 0x%08lx\n",
		       *offset++, temp[i++]);
	}

	return 0;

pipe_display_read_failed:

	return -1;
}

/*
  ======================================================================
  U-Boot Stuff
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_test
*/
  
int
do_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int rc = -1;

	if (0 == strncmp(argv[1], "d", strlen("d"))) {
		if (LSI_DEBUG_ENABLED()) {
			LSI_DEBUG_DISABLE();
		} else {
			LSI_DEBUG_ENABLE();
		}

		rc = 0;
	} else if (0 == strncmp(argv[1], "e", strlen("e"))) {
#ifndef CONFIG_ACP2
#if !defined(NCR_TRACER)
		rc = 0;

		if (3 == argc) {
			if (0 == strncmp(argv[2],
					 "off", strlen("off"))) {
				set_ecc_mode(LSI_NAND_ECC_MODE_OFF);
			} else if (0 == strncmp(argv[2],
						"1bit", strlen("1bit"))) {
				set_ecc_mode(LSI_NAND_ECC_MODE_1BIT);
			} else if (0 == strncmp(argv[2],
						"4bit", strlen("4bit"))) {
				set_ecc_mode(LSI_NAND_ECC_MODE_4BIT);
			} else if (0 == strncmp(argv[2],
						"8bit", strlen("8bit"))) {
				set_ecc_mode(LSI_NAND_ECC_MODE_8BIT);
			} else if (0 == strncmp(argv[2],
						"12bit", strlen("12bit"))) {
				set_ecc_mode(LSI_NAND_ECC_MODE_12BIT);
			} else {
				rc = 1;
			}
		} else {
			printf("ECC Mode is %s\n",
			       get_ecc_mode_string(get_ecc_mode()));
		}
#else
		printf("Not Available when NCR_TRACER is defined!\n");
#endif
#endif
	} else if (0 == strncmp(argv[1], "loc", strlen("loc"))) {
#if !defined(CONFIG_ACP2) && !defined(ACP_EMU) && !defined(ACP_ISS)
		printf("Starting Lock Loop (Ctrl-C to Exit).\n");
		for (;;) {
			if (tstc()) {
				int c = getc();

				if (3 == c)
					break;

				acp_clock_lock_verify(0, 0);
			} else {
				acp_clock_lock_verify(0x10, 0x20000);
			}
		}
#else
		printf("Not Available in the 2nd Stage or Emulation.\n");
#endif
		rc = 0;
	} else if (0 == strncmp(argv[1], "log", strlen("log"))) {
		if (LSI_LOGIO_ENABLED()) {
			LSI_LOGIO_DISABLE();
		} else {
			LSI_LOGIO_ENABLE();
		}

		rc = 0;
	} else if ((0 == strncmp(argv[1], "n", strlen("n"))) &&
		   (5 == argc)) {
#if !defined(CONFIG_ACP2) && defined(CONFIG_LSI_NAND)
		nand_info_t *nand;
		struct nand_chip *chip;
		unsigned long page;
		unsigned long block;
		unsigned long offset_byte;
		unsigned long offset;
		unsigned long bit;
		unsigned long value = 0x100;
		void *buffer = NULL;
		void *oobbuffer = NULL;
		int i;
		int pages;
		struct mtd_oob_ops ops;
		nand_erase_options_t erase_ops;
		lsi_ecc_mode_t original_ecc_mode;
#if defined(ACP_X2V1) || defined(ACP_25xx)
		int section;
#endif
		/*
		  There are erasesize/writesize pages, each with
		  oobsize bytes of oob data in each erase block.
		  Here's the procedure...

		  1) Read the entire erase block (with OOB data).
		  2) Erase the block.
		  3) Flip the specified bit.
		  4) Disable ECC.
		  5) Write the modified erase block (with OOB data).
		  6) Enable ECC.

		  Any later read should report an ECC error (at the
		  specified bit).
		*/
		
		nand = &nand_info[0];
		chip = nand->priv;
		pages = nand->erasesize / nand->writesize;

		/* Allocate memory to hold the erase block and OOB. */
		buffer = malloc(pages * (nand->writesize + nand->oobsize));

		if (NULL == buffer) {
			printf("Couldn't allocate 0x%lx byte buffer!\n",
			       (unsigned long)
			       (pages * (nand->writesize + nand->oobsize)));
			rc = -1;
			goto do_test_exit;
		}

		page = simple_strtoul(argv[2], NULL, 16);
		page &= ~(nand->writesize - 1);
		block = page & ~(nand->erasesize - 1);

		offset_byte = simple_strtoul(argv[3], NULL, 16);

#if defined(ACP_X2V1) || defined(ACP_25xx)

		/*
		  The EP501G3 controller stores each section's
		  checksum immediately after the section, instead of
		  in the OOB.  See the EP501G3 TRM for details.

		  Note that the following is only true for 4bit
		  error correction.
		 */

		if (offset_byte < nand->writesize) {
			/*
			  In the normal write area.
			*/

			section = (offset_byte / 512) % (nand->writesize / 512);
			offset_byte += 8 * section;

			/*
			  If offset_byte is past the end of the page, add the
			  unused OOB bytes.
			*/

			if (offset_byte >= nand->writesize) {
				offset_byte += chip->ecc.layout->eccpos[0];
			}
		} else {
			/*
			  In the OOB area.
			*/

			section = (offset_byte - nand->writesize) / 8;
			offset_byte = 512 + (section * 512) + (section * 8) +
				(offset_byte % 8);

			if (section == ((nand->writesize / 512) - 1)) {
				offset_byte += chip->ecc.layout->eccpos[0];
			}
		}

#else

		/*
		  If offset_byte is past the end of the page, add the
		  unused OOB bytes.
		*/

		if (offset_byte >= nand->writesize) {
			offset_byte += chip->ecc.layout->eccpos[0];
		}

#endif

		/*
		  The ECC warning strings (from the driver) use little
		  endian indexing.  So, do the same here...
		 */

		offset_byte = (offset_byte & ~0x3) | ((offset_byte & 0x3) ^ 0x3);

		if (offset_byte > (nand->writesize + nand->oobsize)) {
			printf("byte 0x%lx is out of range (0x%lx)\n",
			       offset_byte, (unsigned long)nand->writesize);
			free(buffer);
			rc = -1;
			goto do_test_exit;
		}

		printf("Page:0x%x Block:0x%x Byte:0x%x\n",
		       page, block, offset_byte);

		if (0 == strncmp(argv[4], "0x", strlen("0x"))) {
			bit = 0;
			value = simple_strtoul(argv[4], NULL, 16);

			if (0xff < value) {
				printf("value must be between 0x00 and 0xff.\n");
				free(buffer);
				rc = -1;
				goto do_test_exit;
			}
		} else {
			bit = simple_strtoul(argv[4], NULL, 16);

			if (bit > 7) {
				printf("bit must be between 0 and 7.\n");
				free(buffer);
				rc = -1;
				goto do_test_exit;
			}
		}

		/* Turn off ECC (if it isn't already). */
		original_ecc_mode = get_ecc_mode();

		if (LSI_NAND_ECC_MODE_OFF != original_ecc_mode)
			set_ecc_mode(LSI_NAND_ECC_MODE_OFF);

		/* Read block (and OOB). */
		set_correct_cecc(0);
		set_display_cecc(0);
		set_display_ucecc(0);

		/* An OOB buffer is required, but not used... */
		oobbuffer = malloc(nand->oobsize);

		if (NULL == oobbuffer) {
			free(buffer);
			printf("Couldn't allocate OOB buffer!\n");
			rc = -1;
			goto do_test_exit;
		}

		for (i = 0; i < pages; ++i) {
			loff_t address;
			unsigned char *p;
			int j;

			memset(&ops, 0, sizeof(struct mtd_oob_ops));
			ops.datbuf =
				(buffer +
				 (i * (nand->writesize + nand->oobsize)));
			ops.oobbuf = oobbuffer;
			ops.len = nand->writesize;
			ops.ooblen = nand->oobsize;
			ops.mode = MTD_OOB_RAW;
			address = (loff_t)(block + i * nand->writesize);

			if (0 != nand->read_oob(nand, address, &ops)) {
				printf("Error reading page %d\n", i);
				free(buffer);
				rc = -1;
				goto do_test_exit;
			}
		}

		free(oobbuffer);
		set_display_ucecc(1);
		set_display_cecc(1);
		set_correct_cecc(1);

#if 0
		{
			/* Display the page data as stored (different on G3). */
			int bufi;
			unsigned char *bufp;

			bufp = buffer;
			bufi = (nand->writesize + nand->oobsize) >> 4;

			while (bufi--) {
				unsigned long temp[3];
	printf("\t"
				       "%02x %02x %02x %02x "
				       "%02x %02x %02x %02x  "
				       "%02x %02x %02x %02x "
				       "%02x %02x %02x %02x\n",
				       *bufp++, *bufp++, *bufp++, *bufp++,
				       *bufp++, *bufp++, *bufp++, *bufp++,
				       *bufp++, *bufp++, *bufp++, *bufp++,
				       *bufp++, *bufp++, *bufp++, *bufp++);
			}
		}
#endif

		offset = buffer + offset_byte;
		printf("BEFORE: 0x%x\n", *((unsigned char *)offset));

		if (0x100 == value) {
			*((unsigned char *)offset) ^= (1 << bit);
		} else {
			*((unsigned char *)offset) = value;
		}

		printf("AFTER: 0x%x\n", *((unsigned char *)offset));

		/* Erase the block */
		memset(&erase_ops, 0, sizeof(nand_erase_options_t));
		erase_ops.offset = (loff_t)block;
		erase_ops.length = nand->erasesize;
		erase_ops.jffs2 = 0;
		erase_ops.quiet = 1;

		if (0 != nand_erase_opts(nand, &erase_ops)) {
			printf("Erase failed!\n");
			free(buffer);
			rc = -1;
			goto do_test_exit;
		}

		/* Write block (and OOB). */
		for (i = 0; i < pages; ++i) {
			loff_t address;

			memset(&ops, 0, sizeof(struct mtd_oob_ops));
			ops.datbuf =
				(buffer +
				 (i * (nand->writesize + nand->oobsize)));
			ops.oobbuf = ops.datbuf + nand->writesize;
			ops.len = nand->writesize;
			ops.ooblen = nand->oobsize;
			ops.mode = MTD_OOB_RAW;
			address = (loff_t)(block + i * nand->writesize);

			if (0 != nand->write_oob(nand, address, &ops)) {
				printf("Error writing page %d\n", i);
				free(buffer);
				rc = -1;
				goto do_test_exit;
			}
		}

		/* Restore the ECC state. */
		if (get_ecc_mode() != original_ecc_mode)
			set_ecc_mode(original_ecc_mode);

		free(buffer);
		rc = 0;
#else
		printf("Only Available in Stage 3\n");
		rc = -1;
#endif
	} else if (0 == strncmp(argv[1], "t", strlen("t"))) {
		printf("%llu\n", get_ticks());
		rc = 0;
	} else if (0 == strncmp(argv[1], "i", strlen("i")) &&
		   5 == argc) {
#if !defined(CONFIG_ACP2) && !defined(ACP_ISS)
		unsigned long offset;
		unsigned long address;
		unsigned long length;

		offset = simple_strtoul(argv[2], NULL, 16);
		address = simple_strtoul(argv[3], NULL, 16);
		length = simple_strtoul(argv[4], NULL, 16);
		printf("Writing 0x%lx bytes from 0x%lx to 0x50,0x%lx\n",
		       length, address, offset);
		i2c_write(0x50, offset, 1, (unsigned char *)address, length);
		rc = 0;
#else
		printf("Not Available in the 2nd Stage or Emulation.\n");
#endif
	} else if (0 == strncmp(argv[1], "m", strlen("m"))) {
#if !defined(CONFIG_ACP2) && !defined(ACP_ISS)
		int interrupt = 90;
		int group = (90 / 20);
		unsigned long value;

		/*
		  Set Up Input 90 (SM0) on MPIC1
		*/

		/* Current Task Priority */
		dcr_write(0, 0xffb00080);

		/* Disable 8259 Bypass Mode */
		dcr_write(0x2000000f, 0xffb01020);

		/* Set the Vector/Priority Register */
		dcr_write(0x008f0000, (0xffb10000 + (interrupt * 0x20)));

		/* Set the Destination Register */
		dcr_write(0x0000000f,
			  (0xffb10000 + ((interrupt * 0x20) + 0x10)));

		printf("Interrupt Enabled in MPIC1, Testing...\n");

		/*
		  Setup active-high mask bits in DENALICTL_90 register
		  0x22.0x0.0x168 so that when bit 18 of DENALICTL_91
		  in 0x22.0x0.0x16c gets set  it will propagate to
		  MPIC source 90.

		  For this you want to ensure that

		  bit 20 of DENALICTL_90 in 0x22.0.0x168 is set to 0

		  bit 19 of DENALICTL_90 in 0x22.0.0x168 is set to 1

		  bit 18 of DENALICTL_90 in 0x22.0.0x168 is set to 0

		  bit 17:0 of DENALICTL_90 in 0x22.0.0x168 is set to 1
		*/

		ncr_read32(NCP_REGION_ID(0x22, 0), 0x168, &value);
		value &= ~0x1fffff;
		value |= 0xbffff;
		ncr_write32(NCP_REGION_ID(0x22, 0), 0x168, value);
#endif
	} else if (0 == strncmp(argv[1], "pc", strlen("pc"))) {
		unsigned long configuration;
		unsigned long mask;
		unsigned long last_value;

		configuration = simple_strtoul(argv[2], NULL, 16);

		if (4 <= argc)
			mask = simple_strtoul(argv[3], NULL, 16);
		else
			mask = 0xffffffffUL;

		printf("Configuration: 0x%08lx  Mask: 0x%08lx\n",
		       configuration, mask);

		acpwriteio(0x80000100, 0xf0983020);
		acpwriteio(configuration, 0xf09830a4);

		last_value = (acpreadio(0xf09830a0) & mask);
		printf("0xf09a30a0 contains 0x%08lx\n", last_value);

		for (;;) {
			unsigned long value;

			value = (acpreadio(0xf09830a0) & mask);

			if (last_value != value) {
				last_value = value;
				printf("0xf09a30a0 contains 0x%08lx\n",
				       last_value);
			}

			if (ctrlc())
				break;
		}

		rc = 0;
	} else if (0 == strncmp(argv[1], "pi", strlen("pi"))) {
		unsigned long value;
		unsigned long mask;
		unsigned long link;
		unsigned long mlink[3];
		unsigned long region;
		unsigned long temp;
		unsigned long last_value;

		region = NCP_REGION_ID(0x115, 2);

		value = simple_strtoul(argv[2], NULL, 16);
		mask = simple_strtoul(argv[3], NULL, 16);
		link = simple_strtoul(argv[4], NULL, 16);

		if (4 <= link)
			goto pipe_bad_input;

		link = 0x64 + (link * 8);

		if (6 <= argc)
			mlink[0] =
				(0x64 + (simple_strtoul(argv[5], NULL, 16) * 8));
		else
			mlink[0] = 0;

		if (7 <= argc)
			mlink[1] =
				(0x64 + (simple_strtoul(argv[6], NULL, 16) * 8));
		else
			mlink[1] = 0;

		if (8 <= argc)
			mlink[2] =
				(0x64 + (simple_strtoul(argv[7], NULL, 16) * 8));
		else
			mlink[2] = 0;

		printf("Pipe: 0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx 0x%08lx\n",
		       value, mask, link, mlink[0], mlink[1], mlink[2]);

		if (0 != ncr_read32(region, 0x4, &temp))
			goto pipe_read_failed;

		temp &= ~0x1fe0;
		temp |= ((value << 5) & 0x1fe0);

		if (0 != ncr_write32(region, 0x4, temp))
			goto pipe_read_failed;

		if (0 != ncr_read32(region, link, &last_value))
			goto pipe_read_failed;

		if (0 != test_pipe_display(region,
					   last_value, link, argc - 5, mlink))
			goto pipe_read_failed;

		for (;;) {
			unsigned long this_value;

			if (0 !=
			    ncr_read32(region, link, &this_value))
				goto pipe_read_failed;

			if ((last_value & mask) != (this_value & mask)) {
				last_value = this_value;

				if (0 != test_pipe_display(region, last_value,
							   link, argc - 5,
							   mlink))
					goto pipe_read_failed;
			}

			if (ctrlc())
				break;
		}

		goto pipe_done;

	pipe_read_failed:

		printf("Config Ring Access Failed!\n");
		goto pipe_done;

	pipe_bad_input:

		printf("Bad Input.\n");
		goto pipe_done;

	pipe_done:
		rc = 0;
	}

	if (0 != rc) {
#ifndef CFG_NOHELP
		printf("%s", cmdtp->usage);
#endif
	}

 do_test_exit:
	return rc;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(test, 9, 0, do_test,
	   "test debug|ecc|pcie|logio|locks|nand|ticks|memory|help\n",
	   "d,ebug  -- Toggle DEBUG logging.\n" \
	   "e,cc    -- Set the ECC mode to the given value.\n" \
	   "log,io  -- Toggle IO logging.\n" \
	   "loc,ks  -- Start the PLL Lock Test.\n" \
	   "n,and   -- Insert error in NAND page (\"page offset\" byte " \
	   "bit|value).\n" \
	   "           bit means flip that bit, value means write that value\n" \
	   "           to specify a value, start with 0x...\n" \
	   "t,icks  -- Display the Return Value from get_ticks().\n" \
	   "m,emory -- Verify the memory fault trigger.\n" \
	   "pc,ie   -- Poll PCIe debug register.\n" \
	   "pi,pe   -- Poll PIPE debug registers\n"
	   "h,elp   -- This Wonderful Help Screen\n");

#endif /* CONFIG_ACP */
