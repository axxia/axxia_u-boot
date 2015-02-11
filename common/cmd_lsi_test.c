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

#ifndef CONFIG_SPL_BUILD

#include <common.h>
#include <command.h>

/*
  ======================================================================
  Local Stuff
  ======================================================================
*/

static void
diff_mem(void *a, void *b, int size)
{
	unsigned char *a_val = a;
	unsigned char *b_val = b;
	int i = 0;

	while (0 < size--) {
		if (*a_val != *b_val)
			printf("At Index 0x%08x: 0x%02x != 0x%02x\n",
			       i, *a_val, *b_val);

		++a_val;
		++b_val;
		++i;
	}
}

static int
check_mem(void *mem, int pattern, int size)
{
	unsigned char *value = mem;
	int i = 0;
	int rc = 0;

	while (0 < size--) {
		if (*value != (unsigned char)pattern) {
			printf("At Index 0x%08x: 0x%02x != 0x%02x\n",
			       i, *value, (unsigned char)pattern);
			rc = 1;
		}

		++value;
		++i;
	}

	return rc;
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
do_test(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int rc;

        if (0 == strncmp(argv[1], "h", strlen("h"))) {
                printf("%s", cmdtp->usage);

                return CMD_RET_SUCCESS;
        }

	if (0 == strncmp(argv[1], "l", strlen("l"))) {
		int i = 0;
		void *memory = (void *)0x10000000ULL;
		void *lsm = (void *)LSM;
		int pattern = 0x11;

		/* Start the test. */
		for (;;) {
			printf("Starting Iteration %3d (Ctrl-C to Quit): ", i);

			/* Set up the pattern area. */
			printf("initializing... ");
			memset(memory, pattern, 0x40000);

			rc = check_mem(memory, pattern, 0x40000);

			if (0 != rc) {
				printf("\n%s:%d - Pattern Lost!\n",
				       __FILE__, __LINE__);

				return CMD_RET_FAILURE;
			}

			/* Write to LSM */
			printf("writing... ");
			memcpy(lsm, memory, 0x40000);

			rc = check_mem(memory, pattern, 0x40000);

			if (0 != rc) {
				printf("\n%s:%d - Pattern Lost!\n",
				       __FILE__, __LINE__);

				return CMD_RET_FAILURE;
			}

			printf("comparing...\n");
			rc = memcmp(memory, lsm, 0x40000);

			if (0 != rc) {
				printf("\n%s:%d - Compare Failed!\n",
				       __FILE__, __LINE__);
				diff_mem(memory, lsm, 0x40000);

				return CMD_RET_FAILURE;
			}

			/* Check for exit... */
			if (ctrlc())
				return CMD_RET_SUCCESS;

			++i;

			/* Update the pattern. */
			pattern = ~pattern;
		}
	}

	return CMD_RET_USAGE;
}

/*
  ======================================================================
  Command Definitions
  ======================================================================
*/

U_BOOT_CMD(test, 5, 0, do_test,
	   "test help|lsm",
	   "h,elp   -- Long help.\n" \
	   "l,sm    -- Run the LSM memory test.");

#endif /* CONFIG_SPL_BUILD */
