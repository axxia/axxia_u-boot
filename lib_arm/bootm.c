/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * Copyright (C) 2001  Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
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
 *
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#if defined (CONFIG_SETUP_MEMORY_TAGS) || \
    defined (CONFIG_CMDLINE_TAG) || \
    defined (CONFIG_INITRD_TAG) || \
    defined (CONFIG_SERIAL_TAG) || \
    defined (CONFIG_REVISION_TAG) || \
    defined (CONFIG_VFD) || \
    defined (CONFIG_LCD)
static void setup_start_tag (bd_t *bd);

# ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags (bd_t *bd);
# endif
static void setup_commandline_tag (bd_t *bd, char *commandline);

# ifdef CONFIG_INITRD_TAG
static void setup_initrd_tag (bd_t *bd, ulong initrd_start,
			      ulong initrd_end);
# endif
static void setup_end_tag (bd_t *bd);

# if defined (CONFIG_VFD) || defined (CONFIG_LCD)
static void setup_videolfb_tag (gd_t *gd);
# endif

static struct tag *params;
#endif /* CONFIG_SETUP_MEMORY_TAGS || CONFIG_CMDLINE_TAG || CONFIG_INITRD_TAG */

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	bd_t	*bd = gd->bd;
	char	*s;
	int	machid = bd->bi_arch_number;
	void	(*theKernel)(int zero, int arch, uint params);

#ifdef CONFIG_CMDLINE_TAG
	char *commandline = getenv ("bootargs");
#ifdef CONFIG_APP
    char full_command_line [ 512 ];
    char *mtdparts = getenv ("mtdparts");
    memset( full_command_line, 0, 512 );
    strcpy( full_command_line, commandline );
    strcat( full_command_line, " " );
    strcat( full_command_line, mtdparts );
    commandline = full_command_line;
#endif  /* CONFIG_APP */
#endif  /* CONFIG_CMDLINE_TAG */

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO))
		return 1;

	theKernel = (void (*)(int, int, uint))images->ep;

	s = getenv ("machid");
	if (s) {
		machid = simple_strtoul (s, NULL, 16);
		printf ("Using machid 0x%x from environment\n", machid);
	}

	show_boot_progress (15);

	debug ("## Transferring control to Linux (at address %08lx) ...\n",
	       (ulong) theKernel);

#if defined (CONFIG_SETUP_MEMORY_TAGS) || \
    defined (CONFIG_CMDLINE_TAG) || \
    defined (CONFIG_INITRD_TAG) || \
    defined (CONFIG_SERIAL_TAG) || \
    defined (CONFIG_REVISION_TAG) || \
    defined (CONFIG_LCD) || \
    defined (CONFIG_VFD)
	setup_start_tag (bd);
#ifdef CONFIG_SERIAL_TAG
	setup_serial_tag (&params);
#endif
#ifdef CONFIG_REVISION_TAG
	setup_revision_tag (&params);
#endif
#ifdef CONFIG_SETUP_MEMORY_TAGS
	setup_memory_tags (bd);
#endif
#ifdef CONFIG_CMDLINE_TAG
	setup_commandline_tag (bd, commandline);
#endif
#ifdef CONFIG_INITRD_TAG
	if (images->rd_start && images->rd_end)
		setup_initrd_tag (bd, images->rd_start, images->rd_end);
#endif
#if defined (CONFIG_VFD) || defined (CONFIG_LCD)
	setup_videolfb_tag ((gd_t *) gd);
#endif
#ifdef CONFIG_APP
    setup_app_tag (bd);
#endif  /* CONFIG_APP */
	setup_end_tag (bd);
#endif

#ifdef LSI_ARCH_APP3K

    {

      int cores_ [ 4 ] = { 0, 0, 0, 0 };
      unsigned long temp_;
      int index_;
      extern unsigned long _secondary_start_address;
      extern volatile unsigned long _secondary_in_progress;

      _secondary_start_address = ep;
      temp_ = ( readl( CONFIG_NORMAL_AEI_BASE ) & 0xf );
      if( 0 != ( temp_ & 0x1 ) ) { cores_ [ 0 ] = 1; }
      if( 0 != ( temp_ & 0x2 ) ) { cores_ [ 1 ] = 1; }
      if( 0 != ( temp_ & 0x4 ) ) { cores_ [ 2 ] = 1; }
      if( 0 != ( temp_ & 0x8 ) ) { cores_ [ 3 ] = 1; }

      if( ( 0 != cores_ [ 1 ] ) ||
          ( 0 != cores_ [ 2 ] ) ||
          ( 0 != cores_ [ 3 ] ) ) {

        writel( 1, PMR_CII_CONTROL );
        writel( 1, PMR_GID_CONTROL );

        for( index_ = 1; index_ < 4; ++ index_ ) {

          if( 0 == cores_ [ index_ ] ) { continue; }
          printf( "Starting core %d\n", index_ );
          _secondary_in_progress = 0;
          writel( 1, ( CONFIG_NORMAL_PMR_BASE + 0x300 ) );
          writel( ( ( 1 << ( 16 + index_ ) ) | 1 ),
                  PMR_GID_SOFTWARE_INTERRUPT );
          printf( "Interrupted core %d\n", index_ );

          while( 1 != _secondary_in_progress ) {

            writel( ( ( 1 << ( 16 + index_ ) ) | 1 ),
                    PMR_GID_SOFTWARE_INTERRUPT );

          }

          _secondary_in_progress = 2;
          printf( "Sent core %d to Linux\n", index_ );

          while( 0 != _secondary_in_progress ) {

            unsigned long temp_ = readl( ( CONFIG_NORMAL_ASI_BASE + 0x180 ) );
            ++ temp_;
            writel( temp_, ( CONFIG_NORMAL_ASI_BASE + 0x180 ) );

          }

          printf( "Started core %d\n", index_ );

        }

      }

    }

#endif

	/* we assume that the kernel is in place */
	printf ("\nStarting kernel ...\n\n");

#ifdef CONFIG_USB_DEVICE
	{
		extern void udc_disconnect (void);
		udc_disconnect ();
	}
#endif

	cleanup_before_linux ();

#ifdef LSI_ARCH_APP3
    REMAP_RESET( );
#endif

	theKernel (0, machid, bd->bi_boot_params);
	/* does not return */

	return 1;
}


#if defined (CONFIG_SETUP_MEMORY_TAGS) || \
    defined (CONFIG_CMDLINE_TAG) || \
    defined (CONFIG_INITRD_TAG) || \
    defined (CONFIG_SERIAL_TAG) || \
    defined (CONFIG_REVISION_TAG) || \
    defined (CONFIG_LCD) || \
    defined (CONFIG_VFD)
static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *) bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}


#ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags (bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem32);

		params->u.mem.start = bd->bi_dram[i].start;
		params->u.mem.size = bd->bi_dram[i].size;

		params = tag_next (params);
	}
}
#endif /* CONFIG_SETUP_MEMORY_TAGS */


static void setup_commandline_tag (bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}


#ifdef CONFIG_INITRD_TAG
static void setup_initrd_tag (bd_t *bd, ulong initrd_start, ulong initrd_end)
{
	/* an ATAG_INITRD node tells the kernel where the compressed
	 * ramdisk can be found. ATAG_RDIMG is a better name, actually.
	 */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size (tag_initrd);

	params->u.initrd.start = initrd_start;
	params->u.initrd.size = initrd_end - initrd_start;

	params = tag_next (params);
}
#endif /* CONFIG_INITRD_TAG */


#if defined (CONFIG_VFD) || defined (CONFIG_LCD)
extern ulong calc_fbsize (void);
static void setup_videolfb_tag (gd_t *gd)
{
	/* An ATAG_VIDEOLFB node tells the kernel where and how large
	 * the framebuffer for video was allocated (among other things).
	 * Note that a _physical_ address is passed !
	 *
	 * We only use it to pass the address and size, the other entries
	 * in the tag_videolfb are not of interest.
	 */
	params->hdr.tag = ATAG_VIDEOLFB;
	params->hdr.size = tag_size (tag_videolfb);

	params->u.videolfb.lfb_base = (u32) gd->fb_base;
	/* Fb size is calculated according to parameters for our panel
	 */
	params->u.videolfb.lfb_size = calc_fbsize();

	params = tag_next (params);
}
#endif /* CONFIG_VFD || CONFIG_LCD */

#ifdef CONFIG_SERIAL_TAG
void setup_serial_tag (struct tag **tmp)
{
	struct tag *params = *tmp;
	struct tag_serialnr serialnr;
	void get_board_serial(struct tag_serialnr *serialnr);

	get_board_serial(&serialnr);
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = serialnr.low;
	params->u.serialnr.high= serialnr.high;
	params = tag_next (params);
	*tmp = params;
}
#endif

#ifdef CONFIG_REVISION_TAG
void setup_revision_tag(struct tag **in_params)
{
	u32 rev = 0;
	u32 get_board_rev(void);

	rev = get_board_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}
#endif  /* CONFIG_REVISION_TAG */

#ifdef CONFIG_APP
static void setup_app_tag(bd_t *bd)
{
  params->hdr.tag = ATAG_APP;
  params->hdr.size = tag_size(tag_app);
#if defined( LSI_ARCH_APP3K )
  params->u.app.core_speed = ( pll_get_clock( axi ) * 2 );
  params->u.app.host_speed = pll_get_clock( ipsec );
#elif defined( LSI_ARCH_APP3 )
  params->u.app.core_speed = pll_get_clock( arm_core );
  params->u.app.host_speed = pll_get_clock( host );
#else
#error "Unknown Architecture"
#endif
  params->u.app.uboot_size = CFG_MONITOR_LEN;
  params->u.app.ubootenv0_size = CFG_ENV_SIZE;
#ifdef CFG_ENV_ADDR_REDUND
  params->u.app.ubootenv1_size = CFG_ENV_SIZE_REDUND;
#else  /* CFG_ENV_ADDR_REDUND */
  params->u.app.ubootenv1_size = 0;
#endif /* CFG_ENV_ADDR_REDUND */
  params->u.app.pci_sm = ( u32 ) app_is_pci_sm( );
  params = tag_next(params);
}
#endif /* CONFIG_APP */

static void setup_end_tag (bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

#endif /* CONFIG_SETUP_MEMORY_TAGS || CONFIG_CMDLINE_TAG || CONFIG_INITRD_TAG */
