/*
 * common/cmd_lsi_sbb.c
 *
 * (C) Copyright 2011
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

/*#define LSI_DEBUG*/
#define LSI_WARN
/*#define LSI_LOGIO*/
#include <config.h>

#ifdef CONFIG_ACP

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <nand.h>

/*
  ======================================================================
  Local
  ======================================================================
*/

/*
  ======================================================================
  Public
  ======================================================================
*/

/*
  ----------------------------------------------------------------------
  do_sbb
*/
  
int
do_sbb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int rc = -1;
	unsigned long source;
	unsigned long destination;

	if (0 == strncmp(argv[1], "v", strlen("v"))) {
		int safe = 0;

		if ((5 == argc) && (0 == strncmp(argv[4], "s", strlen("s"))))
			safe = 1;

		source = simple_strtoul(argv[2], NULL, 16);
		destination = simple_strtoul(argv[3], NULL, 16);

		if (0 == sbb_verify_image((void *)source, (void *)destination, safe))
			rc = 0;
	} else if (0 == strncmp(argv[1], "e", strlen("e"))) {
		unsigned long size;

		source = simple_strtoul(argv[2], NULL, 16);
		destination = simple_strtoul(argv[3], NULL, 16);
		size = simple_strtoul(argv[4], NULL, 16);

		if (0 == sbb_encrypt_range((void *)source, (void *)destination, size))
			rc = 0;
	} else if (0 == strncmp(argv[1], "d", strlen("d"))) {
		int safe = 0;

		if ((5 == argc) && (0 == strncmp(argv[4], "s", strlen("s"))))
			safe = 1;

		source = simple_strtoul(argv[2], NULL, 16);
		destination = simple_strtoul(argv[3], NULL, 16);

		if (0 == sbb_decrypt_range((void *)source, (void *)destination, safe))
			rc = 0;
	}

#if 0
	if (((0 == strncmp(argv[1], "d", strlen("d"))) ||
	     (0 == strncmp(argv[1], "v", strlen("v")))) &&
	    (4 == argc)) {
		unsigned long source;
		unsigned long destination;
		int double_read = 0;

		if (0 == strncmp(argv[1], "d", strlen("d")))
			double_read = 1;

		source = simple_strtoul(argv[2], NULL, 16);
		destination = simple_strtoul(argv[3], NULL, 16);

		if (0 != sbb_verify_image((void *)source, (void *)destination,
					  double_read)) {
			printf("verify failed!\n");
		} else {
			rc = 0;
		}
	}
#endif

	if (0 != rc) {
		printf("%s", cmdtp->usage);
	}

 do_test_exit:
	return rc;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(sbb, 5, 0, do_sbb,
	   "sbb command source destination [size (encrrypt only)] [safe]\n",
	   "     command must be validate|encrypt|decrypt\n" \
	   "     v,alidate -- Validate Image (safe for double read)\n" \
	   "     e,ncrypt  -- Encrypt Memory Region\n" \
	   "     d,ecrypt  -- Decrypt Memory Region (safe for double read)\n");

#endif /* CONFIG_ACP */
