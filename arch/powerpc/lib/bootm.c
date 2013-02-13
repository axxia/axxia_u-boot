/*
 * (C) Copyright 2008 Semihalf
 *
 * (C) Copyright 2000-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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


#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <image.h>
#include <malloc.h>
#include <u-boot/zlib.h>
#include <bzlib.h>
#include <environment.h>
#include <asm/byteorder.h>
#include <asm/mp.h>
#include <asm/processor.h>
#include <asm/io.h>

#if defined(CONFIG_OF_LIBFDT)
#include <fdt.h>
#include <libfdt.h>
#include <fdt_support.h>

#endif

#define DEBUG

#ifdef CONFIG_SYS_INIT_RAM_LOCK
#include <asm/cache.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern ulong get_effective_memsize(void);
static ulong get_sp (void);
static void set_clocks_in_mhz (bd_t *kbd);

#ifndef CONFIG_SYS_LINUX_LOWMEM_MAX_SIZE
#define CONFIG_SYS_LINUX_LOWMEM_MAX_SIZE	(768*1024*1024)
#endif

#ifdef CONFIG_ACP3

void board_reset(void);

static void
boot_jump_linux(bootm_headers_t *images)
{
	char *new_commandline;
	char *bootargs;
	char *mtdparts = getenv("mtdparts");
	char *baudrate = getenv("baudrate");
	int group;
	int core;
	int cores;
	unsigned long os_base;
	char *ccr0_env;
	char *ccr1_env;
	char *ccr2_env;
	unsigned long ccr0_val;
	unsigned long ccr1_val;
	unsigned long ccr2_val;
	void (*kernel)(bd_t *, ulong, ulong, ulong, ulong);
	int rc;
	struct fdt_header *dt;

	__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));
	group = acp_osg_get_current();
	dt = get_acp_fdt(group);
	os_base = (acp_osg_group_get_res(group, ACP_OS_BASE) * 1024 * 1024);
	printf("Booting OS Group: core %d, group %d, fdt 0x%08x\n",
	       core, group, dt);

	/* Update the command line */
	new_commandline = calloc(512, 1);

	if ((char *)0 == new_commandline) {
		printf("Unable to update the command line.\n");
		goto error;
	}

	switch (group) {
	case 0:
		bootargs = getenv("osgroup0_bootargs");
		break;
	case 1:
		bootargs = getenv("osgroup1_bootargs");
		break;
	case 2:
		bootargs = getenv("osgroup2_bootargs");
		break;
	case 3:
		bootargs = getenv("osgroup3_bootargs");
		break;
	default:
		goto error;
		break;
	}

	if (NULL == bootargs)
		bootargs = getenv("bootargs3");

	if ((char *)0 != bootargs) {
		strcat(new_commandline, bootargs);

		if((char *)0 != mtdparts) {
			strcat(new_commandline, " ");
			strcat(new_commandline, mtdparts);
		}
	}

	printf("Linux Command Line: %s\n", new_commandline);

	rc = fdt_find_and_setprop(dt, "/chosen", "bootargs",
				  new_commandline,
				  strlen(new_commandline) + 1, 1);

	if(0 != rc) {
		printf("Unable to set bootargs: %d.\n", rc);
		goto error;
	}

	free(new_commandline);

	/* Set up the memory definition in the device tree. */
	printf("Updating /memory reg\n");
	{
		unsigned long value[3];

		value[0] = 0x00000000;
		value[1] = os_base;
		value[2] =
		  (acp_osg_group_get_res(group, ACP_OS_SIZE) * 1024 * 1024);

		rc = fdt_find_and_setprop(dt, "/memory", "reg",
					  (void *)value, sizeof(value), 1);

		if(0 != rc) {
			printf("Unable to set /memory reg: %d.\n", rc);
			goto error;
		}
	}

	if (0 != images->initrd_start && 0 != images->initrd_end) {
		rc = fdt_find_and_setprop(dt, "/chosen",
					  "linux,initrd-start",
					  (void *)&images->initrd_start,
					  sizeof(unsigned long), 1);
		rc |= fdt_find_and_setprop(dt, "/chosen",
					   "linux,initrd-end",
					   (void *)&images->initrd_end,
					   sizeof(unsigned long), 1);

		if (0 != rc) {
			printf("Unable to set up the ramdisk.\n");
			goto error;
		}
	}

	/* Set up secondary cores. */
	cores = acp_osg_group_get_res(group, ACP_OS_CORES);
	cores &= ~acp_osg_group_get_res(group, ACP_OS_BOOT_CORE);

	if (NULL != (ccr0_env = getenv("ccr0")))
	  ccr0_val = simple_strtoul(ccr0_env, NULL, 16);
	else
	  ccr0_val = CCR0_DEFAULT;

	if (NULL != (ccr1_env = getenv("ccr1")))
	  ccr1_val = simple_strtoul(ccr1_env, NULL, 16);
	else
	  ccr1_val = CCR1_DEFAULT;

	if (NULL != (ccr2_env = getenv("ccr2")))
	  ccr2_val = simple_strtoul(ccr2_env, NULL, 16);
	else
	  ccr2_val = CCR2_DEFAULT;

	printf("CCR0=0x%08lx CCR1=0x%08lx CCR2=0x%08lx\n",
	       ccr0_val, ccr1_val, ccr2_val );

	if (0 != cores) {
		for (core = 0; core < ACP_NR_CORES; ++core) {
			if (0 == ((1 << core) & cores))
				continue;
			(acp_spintable[core])->ccr0_value = ccr0_val;
			(acp_spintable[core])->ccr1_value = ccr1_val;
			(acp_spintable[core])->ccr2_value = ccr2_val;
		}
	}

	/* Remove unused cores from the device tree. */
	for (core = 0; core < ACP_NR_CORES; ++core) {
		int nodeoffset;
		char buffer[20];

		if ((0 != ((1 << core) & cores)) ||
		    ((1 << core) ==
		     acp_osg_group_get_res(group, ACP_OS_BOOT_CORE)))
			continue;

		sprintf(buffer, "/cpus/cpu@%d", core);
		nodeoffset = fdt_path_offset(dt, buffer);

		if (0 > nodeoffset) {
			printf("Error Getting Offset of %s.\n", buffer);
			goto error;
		}

		fdt_del_node(dt, nodeoffset);
	}

	/* Update the CCRn values for the boot core. */
	mtspr( ccr0, ccr0_val );
	mtspr( ccr1, ccr1_val );
	mtspr( ccr2, ccr2_val );
	isync( );

	/* Boot Linux */
	kernel = (void (*)(bd_t *, ulong, ulong, ulong, ulong))images->ep;
#ifdef CONFIG_ACP3
	/* If necessary, Copy the device tree. */
	if (0 != os_base) {
		rc = fdt_open_into(dt,
				   os_base,
				   fdt_totalsize(dt));

		if (0 != rc) {
			printf("Unable to copy device tree!\n");
			goto error;
		}

		dt = (struct fdt_header *)os_base;
	}

	acp_osg_set_os(group, kernel, (unsigned long)dt,
		       (unsigned long)kernel, 0, 0, 0);
#else
	/* Release the stage 3 lock. */
	acp_unlock_stage3();

	(*kernel)((bd_t *)dt, (ulong)kernel, 0, 0, 0);
#endif

 error:

#ifndef CONFIG_ACP
	board_reset();
#endif
	return;
}

#else  /* CONFIG_ACP3 */

static void boot_jump_linux(bootm_headers_t *images)
{
	void	(*kernel)(bd_t *, ulong r4, ulong r5, ulong r6,
			  ulong r7, ulong r8, ulong r9);
#ifdef CONFIG_OF_LIBFDT
	char *of_flat_tree = images->ft_addr;
#endif

	kernel = (void (*)(bd_t *, ulong, ulong, ulong,
			   ulong, ulong, ulong))images->ep;
	debug ("## Transferring control to Linux (at address %08lx) ...\n",
		(ulong)kernel);

	bootstage_mark(BOOTSTAGE_ID_RUN_OS);

#if defined(CONFIG_SYS_INIT_RAM_LOCK) && !defined(CONFIG_E500)
	unlock_ram_in_cache();
#endif

#if defined(CONFIG_OF_LIBFDT)
	if (of_flat_tree) {	/* device tree; boot new style */
		/*
		 * Linux Kernel Parameters (passing device tree):
		 *   r3: pointer to the fdt
		 *   r4: 0
		 *   r5: 0
		 *   r6: epapr magic
		 *   r7: size of IMA in bytes
		 *   r8: 0
		 *   r9: 0
		 */
		debug ("   Booting using OF flat tree...\n");
		WATCHDOG_RESET ();
		(*kernel) ((bd_t *)of_flat_tree, 0, 0, EPAPR_MAGIC,
			   getenv_bootm_mapsize(), 0, 0);
		/* does not return */
	} else
#endif
	{
		/*
		 * Linux Kernel Parameters (passing board info data):
		 *   r3: ptr to board info data
		 *   r4: initrd_start or 0 if no initrd
		 *   r5: initrd_end - unused if r4 is 0
		 *   r6: Start of command line string
		 *   r7: End   of command line string
		 *   r8: 0
		 *   r9: 0
		 */
		ulong cmd_start = images->cmdline_start;
		ulong cmd_end = images->cmdline_end;
		ulong initrd_start = images->initrd_start;
		ulong initrd_end = images->initrd_end;
		bd_t *kbd = images->kbd;

		debug ("   Booting using board info...\n");
		WATCHDOG_RESET ();
		(*kernel) (kbd, initrd_start, initrd_end,
			   cmd_start, cmd_end, 0, 0);
		/* does not return */
	}
	return ;
}
#endif /* CONFIG_ACP3 */

void arch_lmb_reserve(struct lmb *lmb)
{
	phys_size_t bootm_size;
	ulong size, sp, bootmap_base;

	bootmap_base = getenv_bootm_low();
	bootm_size = getenv_bootm_size();

#ifdef DEBUG
	if (((u64)bootmap_base + bootm_size) >
	    (CONFIG_SYS_SDRAM_BASE + (u64)gd->ram_size))
		puts("WARNING: bootm_low + bootm_size exceed total memory\n");
	if ((bootmap_base + bootm_size) > get_effective_memsize())
		puts("WARNING: bootm_low + bootm_size exceed eff. memory\n");
#endif

	size = min(bootm_size, get_effective_memsize());
	size = min(size, CONFIG_SYS_LINUX_LOWMEM_MAX_SIZE);

	if (size < bootm_size) {
		ulong base = bootmap_base + size;
		printf("WARNING: adjusting available memory to %lx\n", size);
		lmb_reserve(lmb, base, bootm_size - size);
	}

	/*
	 * Booting a (Linux) kernel image
	 *
	 * Allocate space for command line and board info - the
	 * address should be as high as possible within the reach of
	 * the kernel (see CONFIG_SYS_BOOTMAPSZ settings), but in unused
	 * memory, which means far enough below the current stack
	 * pointer.
	 */
	sp = get_sp();
	debug ("## Current stack ends at 0x%08lx\n", sp);

	/* adjust sp by 4K to be safe */
	sp -= 4096;
	lmb_reserve(lmb, sp, (CONFIG_SYS_SDRAM_BASE + get_effective_memsize() - sp));

#ifdef CONFIG_MP
	cpu_mp_lmb_reserve(lmb);
#endif

	return ;
}

static void boot_prep_linux(bootm_headers_t *images)
{
#ifdef CONFIG_MP
	/*
	 * if we are MP make sure to flush the device tree so any changes are
	 * made visibile to all other cores.  In AMP boot scenarios the cores
	 * might not be HW cache coherent with each other.
	 */
	flush_cache((unsigned long)images->ft_addr, images->ft_len);
#endif
}

static int boot_cmdline_linux(bootm_headers_t *images)
{
	ulong of_size = images->ft_len;
	struct lmb *lmb = &images->lmb;
	ulong *cmd_start = &images->cmdline_start;
	ulong *cmd_end = &images->cmdline_end;

	int ret = 0;

	if (!of_size) {
		/* allocate space and init command line */
		ret = boot_get_cmdline (lmb, cmd_start, cmd_end);
		if (ret) {
			puts("ERROR with allocation of cmdline\n");
			return ret;
		}
	}

	return ret;
}

static int boot_bd_t_linux(bootm_headers_t *images)
{
	ulong of_size = images->ft_len;
	struct lmb *lmb = &images->lmb;
	bd_t **kbd = &images->kbd;

	int ret = 0;

	if (!of_size) {
		/* allocate space for kernel copy of board info */
		ret = boot_get_kbd (lmb, kbd);
		if (ret) {
			puts("ERROR with allocation of kernel bd\n");
			return ret;
		}
		set_clocks_in_mhz(*kbd);
	}

	return ret;
}

/*
 * Verify the device tree.
 *
 * This function is called after all device tree fix-ups have been enacted,
 * so that the final device tree can be verified.  The definition of "verified"
 * is up to the specific implementation.  However, it generally means that the
 * addresses of some of the devices in the device tree are compared with the
 * actual addresses at which U-Boot has placed them.
 *
 * Returns 1 on success, 0 on failure.  If 0 is returned, U-boot will halt the
 * boot process.
 */
static int __ft_verify_fdt(void *fdt)
{
	return 1;
}
__attribute__((weak, alias("__ft_verify_fdt"))) int ft_verify_fdt(void *fdt);

static int boot_body_linux(bootm_headers_t *images)
{
	ulong rd_len;
	struct lmb *lmb = &images->lmb;
	ulong *initrd_start = &images->initrd_start;
	ulong *initrd_end = &images->initrd_end;
#if defined(CONFIG_OF_LIBFDT)
	ulong of_size = images->ft_len;
	char **of_flat_tree = &images->ft_addr;
#endif

	int ret;

#if defined(CONFIG_OF_LIBFDT)
	boot_fdt_add_mem_rsv_regions(lmb, *of_flat_tree);
#endif

	/* allocate space and init command line */
	ret = boot_cmdline_linux(images);
	if (ret)
		return ret;

	/* allocate space for kernel copy of board info */
	ret = boot_bd_t_linux(images);
	if (ret)
		return ret;

	rd_len = images->rd_end - images->rd_start;
	ret = boot_ramdisk_high (lmb, images->rd_start, rd_len, initrd_start, initrd_end);
	if (ret)
		return ret;

#if defined(CONFIG_OF_LIBFDT)
	ret = boot_relocate_fdt(lmb, of_flat_tree, &of_size);
	if (ret)
		return ret;

	/*
	 * Add the chosen node if it doesn't exist, add the env and bd_t
	 * if the user wants it (the logic is in the subroutines).
	 */
	if (of_size) {
		if (fdt_chosen(*of_flat_tree, 1) < 0) {
			puts ("ERROR: ");
			puts ("/chosen node create failed");
			puts (" - must RESET the board to recover.\n");
			return -1;
		}
#ifdef CONFIG_OF_BOARD_SETUP
		/* Call the board-specific fixup routine */
		ft_board_setup(*of_flat_tree, gd->bd);
#endif

		/* Delete the old LMB reservation */
		lmb_free(lmb, (phys_addr_t)(u32)*of_flat_tree,
				(phys_size_t)fdt_totalsize(*of_flat_tree));

		ret = fdt_resize(*of_flat_tree);
		if (ret < 0)
			return ret;
		of_size = ret;

		if (*initrd_start && *initrd_end) {
			of_size += FDT_RAMDISK_OVERHEAD;
			fdt_set_totalsize(*of_flat_tree, of_size);
		}
		/* Create a new LMB reservation */
		lmb_reserve(lmb, (ulong)*of_flat_tree, of_size);

		/* fixup the initrd now that we know where it should be */
		if (*initrd_start && *initrd_end)
			fdt_initrd(*of_flat_tree, *initrd_start, *initrd_end, 1);

		if (!ft_verify_fdt(*of_flat_tree))
			return -1;
	}
#endif	/* CONFIG_OF_LIBFDT */
	return 0;
}

noinline
int do_bootm_linux(int flag, int argc, char * const argv[], bootm_headers_t *images)
{
	int	ret;

	if (flag & BOOTM_STATE_OS_CMDLINE) {
		boot_cmdline_linux(images);
		return 0;
	}

	if (flag & BOOTM_STATE_OS_BD_T) {
		boot_bd_t_linux(images);
		return 0;
	}

	if (flag & BOOTM_STATE_OS_PREP) {
		boot_prep_linux(images);
		return 0;
	}

	if (flag & BOOTM_STATE_OS_GO) {
		boot_jump_linux(images);
		return 0;
	}

	boot_prep_linux(images);
	ret = boot_body_linux(images);
	if (ret)
		return ret;
	boot_jump_linux(images);

	return 0;
}

#ifdef CONFIG_BOOTM_UBOOT
__attribute__((noinline)) int
do_bootm_uboot(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	int ret = 0;
	void (*uboot)(void);

	uboot = (void (*)(void))images->ep;
#ifdef ACP
	__asm__ __volatile__ ("lis            6,0\n"   \
			      "mtspr          27,6\n"  \
			      "mtspr          26,%0\n" \
			      "iccci          %0,%0\n" \
			      "dccci          %0,%0\n" \
			      "rfi\n" : :
			      "r" (uboot));
#else
	(*uboot)();
#endif

	return ret;
}
#endif /* CONFIG_BOOTM_UBOOT */

static ulong get_sp (void)
{
	ulong sp;

	asm( "mr %0,1": "=r"(sp) : );
	return sp;
}

static void set_clocks_in_mhz (bd_t *kbd)
{
	char	*s;

	if ((s = getenv ("clocks_in_mhz")) != NULL) {
		/* convert all clock information to MHz */
		kbd->bi_intfreq /= 1000000L;
		kbd->bi_busfreq /= 1000000L;
#if defined(CONFIG_MPC8220)
		kbd->bi_inpfreq /= 1000000L;
		kbd->bi_pcifreq /= 1000000L;
		kbd->bi_pevfreq /= 1000000L;
		kbd->bi_flbfreq /= 1000000L;
		kbd->bi_vcofreq /= 1000000L;
#endif
#if defined(CONFIG_CPM2)
		kbd->bi_cpmfreq /= 1000000L;
		kbd->bi_brgfreq /= 1000000L;
		kbd->bi_sccfreq /= 1000000L;
		kbd->bi_vco	/= 1000000L;
#endif
#if defined(CONFIG_MPC5xxx)
		kbd->bi_ipbfreq /= 1000000L;
		kbd->bi_pcifreq /= 1000000L;
#endif /* CONFIG_MPC5xxx */
	}
}
