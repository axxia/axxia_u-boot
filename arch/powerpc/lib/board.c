/*
 * (C) Copyright 2000-2011
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
#include <malloc.h>
#include <stdio_dev.h>
#ifdef CONFIG_8xx
#include <mpc8xx.h>
#endif
#ifdef CONFIG_5xx
#include <mpc5xx.h>
#endif
#ifdef CONFIG_MPC5xxx
#include <mpc5xxx.h>
#endif
#if defined(CONFIG_CMD_IDE)
#include <ide.h>
#endif
#if defined(CONFIG_CMD_SCSI)
#include <scsi.h>
#endif
#if defined(CONFIG_CMD_KGDB)
#include <kgdb.h>
#endif
#ifdef CONFIG_STATUS_LED
#include <status_led.h>
#endif
#include <net.h>
#ifdef CONFIG_GENERIC_MMC
#include <mmc.h>
#endif
#include <serial.h>
#ifdef CONFIG_SYS_ALLOC_DPRAM
#if !defined(CONFIG_CPM2)
#include <commproc.h>
#endif
#endif
#include <version.h>
#if defined(CONFIG_BAB7xx)
#include <w83c553f.h>
#endif
#include <dtt.h>
#if defined(CONFIG_POST)
#include <post.h>
#endif
#if defined(CONFIG_LOGBUFFER)
#include <logbuff.h>
#endif
#if defined(CONFIG_SYS_INIT_RAM_LOCK) && defined(CONFIG_E500)
#include <asm/cache.h>
#endif
#ifdef CONFIG_PS2KBD
#include <keyboard.h>
#endif

#ifdef CONFIG_ACP3
#include <libfdt.h>
#endif

#ifdef CONFIG_ADDR_MAP
#include <asm/mmu.h>
#endif

#ifdef CONFIG_MP
#include <asm/mp.h>
#endif

#ifdef CONFIG_BITBANGMII
#include <miiphy.h>
#endif

#ifdef CONFIG_SYS_UPDATE_FLASH_SIZE
extern int update_flash_size(int flash_size);
#endif

#if defined(CONFIG_SC3)
extern void sc3_read_eeprom(void);
#endif

#if defined(CONFIG_CMD_DOC)
void doc_init(void);
#endif
#if defined(CONFIG_HARD_I2C) || \
    defined(CONFIG_SOFT_I2C)
#include <i2c.h>
#endif
#include <spi.h>
#include <nand.h>
#include <asm/io.h>

static char *failed = "*** failed ***\n";

#if defined(CONFIG_OXC) || defined(CONFIG_RMU)
extern flash_info_t flash_info[];
#endif

#if defined(CONFIG_START_IDE)
extern int board_start_ide(void);
#endif
#include <environment.h>

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_SYS_MEM_TOP_HIDE)
#define CONFIG_SYS_MEM_TOP_HIDE	0
#endif

extern ulong __init_end;
extern ulong __bss_end__;
ulong monitor_flash_len;

#if defined(CONFIG_CMD_BEDBUG)
#include <bedbug/type.h>
#endif

/*
 * Utilities
 */

/*
 * All attempts to come up with a "common" initialization sequence
 * that works for all boards and architectures failed: some of the
 * requirements are just _too_ different. To get rid of the resulting
 * mess of board dependend #ifdef'ed code we now make the whole
 * initialization sequence configurable to the user.
 *
 * The requirements for any new initalization function is simple: it
 * receives a pointer to the "global data" structure as it's only
 * argument, and returns an integer return code, where 0 means
 * "continue" and != 0 means "fatal error, hang the system".
 */
typedef int (init_fnc_t)(void);

/*
 * Init Utilities
 *
 * Some of this code should be moved into the core functions,
 * but let's get it working (again) first...
 */

static int init_baudrate(void)
{
	gd->baudrate = getenv_ulong("baudrate", 10, CONFIG_BAUDRATE);
	return 0;
}

/***********************************************************************/

static void __board_add_ram_info(int use_default)
{
	/* please define platform specific board_add_ram_info() */
}

void board_add_ram_info(int)
	__attribute__ ((weak, alias("__board_add_ram_info")));

static int __board_flash_wp_on(void)
{
	/*
	 * Most flashes can't be detected when write protection is enabled,
	 * so provide a way to let U-Boot gracefully ignore write protected
	 * devices.
	 */
	return 0;
}

int board_flash_wp_on(void)
	__attribute__ ((weak, alias("__board_flash_wp_on")));

static void __cpu_secondary_init_r(void)
{
}

void cpu_secondary_init_r(void)
	__attribute__ ((weak, alias("__cpu_secondary_init_r")));

static int init_func_ram(void)
{
#ifdef	CONFIG_BOARD_TYPES
	int board_type = gd->board_type;
#else
	int board_type = 0;	/* use dummy arg */
#endif
	puts("DRAM:  ");

	gd->ram_size = initdram(board_type);

	if (gd->ram_size > 0) {
		print_size(gd->ram_size, "");
		board_add_ram_info(0);
		putc('\n');
		return 0;
	}
	puts(failed);
	return 1;
}

/***********************************************************************/

#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
static int init_func_i2c(void)
{
	puts("I2C:   ");
	i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
	puts("ready\n");
	return 0;
}
#endif

#if defined(CONFIG_HARD_SPI)
static int init_func_spi(void)
{
	puts("SPI:   ");
	spi_init();
	puts("ready\n");
	return 0;
}
#endif

/***********************************************************************/

#if defined(CONFIG_WATCHDOG)
static int init_func_watchdog_init(void)
{
	puts("       Watchdog enabled\n");
	WATCHDOG_RESET();
	return 0;
}

#define INIT_FUNC_WATCHDOG_INIT	init_func_watchdog_init,

static int init_func_watchdog_reset(void)
{
	WATCHDOG_RESET();
	return 0;
}

#define INIT_FUNC_WATCHDOG_RESET	init_func_watchdog_reset,
#else
#define INIT_FUNC_WATCHDOG_INIT		/* undef */
#define INIT_FUNC_WATCHDOG_RESET	/* undef */
#endif /* CONFIG_WATCHDOG */

/*
 * Initialization sequence
 */

#ifndef CONFIG_ACP

static init_fnc_t *init_sequence[] = {
#if defined(CONFIG_MPC85xx) || defined(CONFIG_MPC86xx)
	probecpu,
#endif
#if defined(CONFIG_BOARD_EARLY_INIT_F)
	board_early_init_f,
#endif
#if !defined(CONFIG_8xx_CPUCLK_DEFAULT)
	get_clocks,		/* get CPU and bus clocks (etc.) */
#if defined(CONFIG_TQM8xxL) && !defined(CONFIG_TQM866M) \
    && !defined(CONFIG_TQM885D)
	adjust_sdram_tbs_8xx,
#endif
	init_timebase,
#endif
#ifdef CONFIG_SYS_ALLOC_DPRAM
#if !defined(CONFIG_CPM2)
	dpram_init,
#endif
#endif
#if defined(CONFIG_BOARD_POSTCLK_INIT)
	board_postclk_init,
#endif
	env_init,
#if defined(CONFIG_8xx_CPUCLK_DEFAULT)
	/* get CPU and bus clocks according to the environment variable */
	get_clocks_866,
	/* adjust sdram refresh rate according to the new clock */
	sdram_adjust_866,
	init_timebase,
#endif
	init_baudrate,
	serial_init,
	console_init_f,
	display_options,
#if defined(CONFIG_8260)
	prt_8260_rsr,
	prt_8260_clks,
#endif /* CONFIG_8260 */
#if defined(CONFIG_MPC83xx)
	prt_83xx_rsr,
#endif
	checkcpu,
#if defined(CONFIG_MPC5xxx)
	prt_mpc5xxx_clks,
#endif /* CONFIG_MPC5xxx */
#if defined(CONFIG_MPC8220)
	prt_mpc8220_clks,
#endif
	checkboard,
	INIT_FUNC_WATCHDOG_INIT
#if defined(CONFIG_MISC_INIT_F)
	misc_init_f,
#endif
	INIT_FUNC_WATCHDOG_RESET
#if defined(CONFIG_HARD_I2C) || defined(CONFIG_SOFT_I2C)
	init_func_i2c,
#endif
#if defined(CONFIG_HARD_SPI)
	init_func_spi,
#endif
#ifdef CONFIG_POST
	post_init_f,
#endif
	INIT_FUNC_WATCHDOG_RESET init_func_ram,
#if defined(CONFIG_SYS_DRAM_TEST)
	testdram,
#endif /* CONFIG_SYS_DRAM_TEST */
	INIT_FUNC_WATCHDOG_RESET
	NULL,	/* Terminate this list */
};

#endif /* CONFIG_ACP */

ulong get_effective_memsize(void)
{
#ifndef	CONFIG_VERY_BIG_RAM
	return gd->ram_size;
#else
	/* limit stack to what we can reasonable map */
	return ((gd->ram_size > CONFIG_MAX_MEM_MAPPED) ?
		CONFIG_MAX_MEM_MAPPED : gd->ram_size);
#endif
}

static int __fixup_cpu(void)
{
	return 0;
}

int fixup_cpu(void) __attribute__((weak, alias("__fixup_cpu")));

/*
 * This is the first part of the initialization sequence that is
 * implemented in C, but still running from ROM.
 *
 * The main purpose is to provide a (serial) console interface as
 * soon as possible (so we can see any error messages), and to
 * initialize the RAM so that we can relocate the monitor code to
 * RAM.
 *
 * Be aware of the restrictions: global data is read-only, BSS is not
 * initialized, and stack space is limited to a few kB.
 */

#ifdef CONFIG_LOGBUFFER
unsigned long logbuffer_base(void)
{
	return CONFIG_SYS_SDRAM_BASE + get_effective_memsize() - LOGBUFF_LEN;
}
#endif

void board_init_f(ulong bootflag)
{
#ifndef CONFIG_ACP
	bd_t *bd;
	ulong len, addr, addr_sp;
	ulong *s;
	gd_t *id;
	init_fnc_t **init_fnc_ptr;

#ifdef CONFIG_PRAM
	ulong reg;
#endif

	/* Pointer is writable since we allocated a register for it */
	gd = (gd_t *) (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_GBL_DATA_OFFSET);
	/* compiler optimization barrier needed for GCC >= 3.4 */
	__asm__ __volatile__("":::"memory");

#if !defined(CONFIG_CPM2) && !defined(CONFIG_MPC512X) && \
    !defined(CONFIG_MPC83xx) && !defined(CONFIG_MPC85xx) && \
    !defined(CONFIG_MPC86xx)
	/* Clear initial global data */
	memset((void *) gd, 0, sizeof(gd_t));
#endif

	for (init_fnc_ptr = init_sequence; *init_fnc_ptr; ++init_fnc_ptr)
		if ((*init_fnc_ptr) () != 0)
			hang();

#ifdef CONFIG_POST
	post_bootmode_init();
	post_run(NULL, POST_ROM | post_bootmode_get(NULL));
#endif

	WATCHDOG_RESET();

	/*
	 * Now that we have DRAM mapped and working, we can
	 * relocate the code and continue running from DRAM.
	 *
	 * Reserve memory at end of RAM for (top down in that order):
	 *  - area that won't get touched by U-Boot and Linux (optional)
	 *  - kernel log buffer
	 *  - protected RAM
	 *  - LCD framebuffer
	 *  - monitor code
	 *  - board info struct
	 */
	len = (ulong)&__bss_end__ - CONFIG_SYS_MONITOR_BASE;

	/*
	 * Subtract specified amount of memory to hide so that it won't
	 * get "touched" at all by U-Boot. By fixing up gd->ram_size
	 * the Linux kernel should now get passed the now "corrected"
	 * memory size and won't touch it either. This should work
	 * for arch/ppc and arch/powerpc. Only Linux board ports in
	 * arch/powerpc with bootwrapper support, that recalculate the
	 * memory size from the SDRAM controller setup will have to
	 * get fixed.
	 */
	gd->ram_size -= CONFIG_SYS_MEM_TOP_HIDE;

	addr = CONFIG_SYS_SDRAM_BASE + get_effective_memsize();

#if defined(CONFIG_MP) && (defined(CONFIG_MPC86xx) || defined(CONFIG_E500))
	/*
	 * We need to make sure the location we intend to put secondary core
	 * boot code is reserved and not used by any part of u-boot
	 */
	if (addr > determine_mp_bootpg(NULL)) {
		addr = determine_mp_bootpg(NULL);
		debug("Reserving MP boot page to %08lx\n", addr);
	}
#endif

#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
	/* reserve kernel log buffer */
	addr -= (LOGBUFF_RESERVE);
	debug("Reserving %dk for kernel logbuffer at %08lx\n", LOGBUFF_LEN,
	      addr);
#endif
#endif

#ifdef CONFIG_PRAM
	/*
	 * reserve protected RAM
	 */
	reg = getenv_ulong("pram", 10, CONFIG_PRAM);
	addr -= (reg << 10);	/* size is in kB */
	debug("Reserving %ldk for protected RAM at %08lx\n", reg, addr);
#endif /* CONFIG_PRAM */

	/* round down to next 4 kB limit */
	addr &= ~(4096 - 1);
	debug("Top of RAM usable for U-Boot at: %08lx\n", addr);

#ifdef CONFIG_LCD
#ifdef CONFIG_FB_ADDR
	gd->fb_base = CONFIG_FB_ADDR;
#else
	/* reserve memory for LCD display (always full pages) */
	addr = lcd_setmem(addr);
	gd->fb_base = addr;
#endif /* CONFIG_FB_ADDR */
#endif /* CONFIG_LCD */

#if defined(CONFIG_VIDEO) && defined(CONFIG_8xx)
	/* reserve memory for video display (always full pages) */
	addr = video_setmem(addr);
	gd->fb_base = addr;
#endif /* CONFIG_VIDEO  */

	/*
	 * reserve memory for U-Boot code, data & bss
	 * round down to next 4 kB limit
	 */
	addr -= len;
	addr &= ~(4096 - 1);
#ifdef CONFIG_E500
	/* round down to next 64 kB limit so that IVPR stays aligned */
	addr &= ~(65536 - 1);
#endif

	debug("Reserving %ldk for U-Boot at: %08lx\n", len >> 10, addr);

	/*
	 * reserve memory for malloc() arena
	 */
	addr_sp = addr - TOTAL_MALLOC_LEN;
	debug("Reserving %dk for malloc() at: %08lx\n",
	      TOTAL_MALLOC_LEN >> 10, addr_sp);

	/*
	 * (permanently) allocate a Board Info struct
	 * and a permanent copy of the "global" data
	 */
	addr_sp -= sizeof(bd_t);
	bd = (bd_t *) addr_sp;
	memset(bd, 0, sizeof(bd_t));
	gd->bd = bd;
	debug("Reserving %zu Bytes for Board Info at: %08lx\n",
	      sizeof(bd_t), addr_sp);
	addr_sp -= sizeof(gd_t);
	id = (gd_t *) addr_sp;
	debug("Reserving %zu Bytes for Global Data at: %08lx\n",
	      sizeof(gd_t), addr_sp);

	/*
	 * Finally, we set up a new (bigger) stack.
	 *
	 * Leave some safety gap for SP, force alignment on 16 byte boundary
	 * Clear initial stack frame
	 */
	addr_sp -= 16;
	addr_sp &= ~0xF;
	s = (ulong *) addr_sp;
	*s = 0; /* Terminate back chain */
	*++s = 0; /* NULL return address */
	debug("Stack Pointer at: %08lx\n", addr_sp);

	/*
	 * Save local variables to board info struct
	 */

	bd->bi_memstart = CONFIG_SYS_SDRAM_BASE;	/* start of memory */
	bd->bi_memsize = gd->ram_size;			/* size in bytes */

#ifdef CONFIG_SYS_SRAM_BASE
	bd->bi_sramstart = CONFIG_SYS_SRAM_BASE;	/* start of SRAM */
	bd->bi_sramsize = CONFIG_SYS_SRAM_SIZE;		/* size  of SRAM */
#endif

#if defined(CONFIG_8xx) || defined(CONFIG_8260) || defined(CONFIG_5xx) || \
    defined(CONFIG_E500) || defined(CONFIG_MPC86xx)
	bd->bi_immr_base = CONFIG_SYS_IMMR;	/* base  of IMMR register     */
#endif
#if defined(CONFIG_MPC5xxx)
	bd->bi_mbar_base = CONFIG_SYS_MBAR;	/* base of internal registers */
#endif
#if defined(CONFIG_MPC83xx)
	bd->bi_immrbar = CONFIG_SYS_IMMR;
#endif
#if defined(CONFIG_MPC8220)
	bd->bi_mbar_base = CONFIG_SYS_MBAR;	/* base of internal registers */
	bd->bi_inpfreq = gd->inp_clk;
	bd->bi_pcifreq = gd->pci_clk;
	bd->bi_vcofreq = gd->vco_clk;
	bd->bi_pevfreq = gd->pev_clk;
	bd->bi_flbfreq = gd->flb_clk;

	/* store bootparam to sram (backward compatible), here? */
	{
		u32 *sram = (u32 *) CONFIG_SYS_SRAM_BASE;

		*sram++ = gd->ram_size;
		*sram++ = gd->bus_clk;
		*sram++ = gd->inp_clk;
		*sram++ = gd->cpu_clk;
		*sram++ = gd->vco_clk;
		*sram++ = gd->flb_clk;
		*sram++ = 0xb8c3ba11;	/* boot signature */
	}
#endif

	WATCHDOG_RESET();
	bd->bi_intfreq = gd->cpu_clk;	/* Internal Freq, in Hz */
	bd->bi_busfreq = gd->bus_clk;	/* Bus Freq,      in Hz */
#if defined(CONFIG_CPM2)
	bd->bi_cpmfreq = gd->cpm_clk;
	bd->bi_brgfreq = gd->brg_clk;
	bd->bi_sccfreq = gd->scc_clk;
	bd->bi_vco = gd->vco_out;
#endif /* CONFIG_CPM2 */
#if defined(CONFIG_MPC512X)
	bd->bi_ipsfreq = gd->ips_clk;
#endif /* CONFIG_MPC512X */
#if defined(CONFIG_MPC5xxx)
	bd->bi_ipbfreq = gd->ipb_clk;
	bd->bi_pcifreq = gd->pci_clk;
#endif /* CONFIG_MPC5xxx */
	bd->bi_baudrate = gd->baudrate;	/* Console Baudrate     */

#ifdef CONFIG_SYS_EXTBDINFO
	strncpy((char *) bd->bi_s_version, "1.2", sizeof(bd->bi_s_version));
	strncpy((char *) bd->bi_r_version, U_BOOT_VERSION,
		sizeof(bd->bi_r_version));

	bd->bi_procfreq = gd->cpu_clk;	/* Processor Speed, In Hz */
	bd->bi_plb_busfreq = gd->bus_clk;
#if defined(CONFIG_405GP) || defined(CONFIG_405EP) || \
    defined(CONFIG_440EP) || defined(CONFIG_440GR) || \
    defined(CONFIG_440EPX) || defined(CONFIG_440GRX)
	bd->bi_pci_busfreq = get_PCI_freq();
	bd->bi_opbfreq = get_OPB_freq();
#elif defined(CONFIG_XILINX_405)
	bd->bi_pci_busfreq = get_PCI_freq();
#endif
#endif

	debug("New Stack Pointer is: %08lx\n", addr_sp);

	WATCHDOG_RESET();

	gd->relocaddr = addr;	/* Store relocation addr, useful for debug */

	memcpy(id, (void *) gd, sizeof(gd_t));

	relocate_code(addr_sp, id, addr);

	/* NOTREACHED - relocate_code() does not return */
#endif /* CONFIG_ACP */
}

/*
  ----------------------------------------------------------------------
  acp_init_f

  ACP early initialization routine.
*/

void acp_mem_init( unsigned long, unsigned long, unsigned long );
void acp_init_r( void );

void
acp_init_f( void )
{
	bd_t *bd;
	register unsigned long addr;
	unsigned long *s;
	unsigned long core;
#if defined(CONFIG_ACP3)
	unsigned long cold_start;
#endif
#if !defined(ACP_25xx)
	unsigned long l2version;
	unsigned long l2revision;
#endif

#if defined(ACP_25xx) && defined(CONFIG_ACP2) && defined(RESET_INSTEAD_OF_IPI)
	/*
	  Disable core 1.

	  The 25xx will only run at 1100 MHz with core 1 disabled.
	*/

	core = dcr_read(0xd00);
	core |= 0xab;
	dcr_write(core, 0xd00);

	dcr_write(0x2, (DCR_RESET_BASE + 2));
	dcr_write(0x2, (DCR_RESET_BASE + 1));
#endif

	/* Get the core number. */
	__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));

#if !defined(ACP_ISS) && defined(ACP_X1V1)
	/*
	  Add work around recommended by IBM.  ``Force
	  inclusion status of L1 cache lines in the L2 when
	  the L2 is sending snoop invalidates (kills) to the
	  L1.''
	*/
	dcr_write(0x610, (0x300 + (0x100 * core)));
	dcr_write(1, (0x304 + (0x100 * core)));
#endif

#ifdef CONFIG_ACP3
	/*
	  Handle SMP/AMP.

	  Only core 0 should be here if this is a cold start; all
	  other cores should be in the "wait for interrupt state" (1st
	  stage).
	*/

	/* Is this a cold reset? */
#if defined(ACP_25xx) && !defined(ACP_EMU)
	cold_start = dcr_read(DCR_RESET_BASE + 0xe) & 0xf;
	cold_start |= dcr_read(DCR_RESET_BASE + 0x8) & 0x3;
	cold_start |= dcr_read(DCR_RESET_BASE + 0x6) & 0x3;
#else
	cold_start = (0 != (0x00ffe000 & dcr_read((DCR_RESET_BASE + 1))));
#endif

	/* Fail if this is a cold start, and not core 0. */
	if (cold_start && (SYSTEM_BOOTCORE != core))
		acp_failure(__FILE__, __FUNCTION__, __LINE__);

	/* Initialize the Stage 3 Lock. */
	if (cold_start && (SYSTEM_BOOTCORE == core)) {
		acp_initialize_stage3_lock();
		acp_osg_group_set_res(0, ACP_OS_BOOT_CORE, 0);
	}

	/* All secondary cores should spin. */
	if (!acp_osg_is_boot_core(core)) {
		if (-1 == acp_osg_map(acp_osg_get_group(core)))
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		acp_spintable_spin();
	}

	/* Only one boot core at a time... */
	acp_lock_stage3();

	/* Restore this core's copy of the "data" section. */
	if (SYSTEM_BOOTCORE == core) {
		void *source[] = {
			(void *)&_core_copy_core0,
			(void *)&_core_copy_core1,
#if !defined(CONFIG_AXXIA_342X) || !defined(ACP_25xx)
			(void *)&_core_copy_core2,
			(void *)&_core_copy_core3
#endif
		};

		memcpy((void *)&_core_copy_beginning, source[0],
		       (&_core_copy_end - &_core_copy_beginning) * 4);
	} else {
		if (-1 == acp_osg_map(acp_osg_get_group(core)))
			acp_failure(__FILE__, __FUNCTION__, __LINE__);

		acp_osg_jump_to_os(acp_osg_get_group(core));
	}
#endif /* CONFIG_ACP3 */

	/* Initialize the serial port. */
	serial_early_init();

	/*
	  Work around for the problem described in the L2 errata document.

	  "L2 store re-ordering with address match collision".

	  All versions of the L2 before 1.4 are affected.
	*/

#ifndef ACP_25xx
	dcr_write(0xc, 0x300);	/* 0x300 is L2[0] on 34xx */
	l2version = dcr_read(0x304);
	l2revision = l2version & 0xff;
	l2version = (l2version & 0xfff00) >> 8;
	/*printf("L2 Version/Revision: 0x%x/0x%x\n", l2version, l2revision);*/

	if ((1 < l2version) ||
	    ((1 == l2version) && (4 <= l2revision))) {
		unsigned long value;

		dcr_write(0xc10, (0x300 + (0x100 * core)));
		value = dcr_read((0x304 + (0x100 * core)));
		value |= 0x4;
		dcr_write(0xc10, (0x300 + (0x100 * core)));
		dcr_write(value, (0x304 + (0x100 * core)));
	}
#endif

#ifdef CONFIG_ACP2
#ifndef ACP_ISS
	/* Make all P2A access up to the ROM alias be 32b.  See BZ 32127. */
	/*dcr_write(0x00300000, 0x1000);*/
#ifdef ACP_X1V1
	dcr_write(0x00210000, 0x1000);
#else
	dcr_write(0x00214000, 0x1000);
#endif

	/* Initialize voltage, clocks, and system memory */
	if( 0 != acp_init( ) ) {
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
	}

	/* Work around for syscache defect 30980 (only for X1). */
#ifdef ACP_X1V1
	dcr_write( 0x7f082600, 0xf03 );
#endif

	/*
	  Update the TLB entry for system memory (change WIMG to 0010).

	  Note that this should be 1G to allow the VxWorks 3rd stage
	  to boot.
	*/

	__asm__ __volatile__ ("tlbwe		%1,%0,0\n" \
			      "tlbwe		%2,%0,1\n" \
			      "tlbwe		%3,%0,2\n" \
			      "isync\n" : :
			      "r" (0x80000000),
			      "r" (0x00000bf0),
			      "r" (0x00000000),
			      "r" (ACP_CACHE_TLB));

#endif /* ACP_ISS */
#endif /* CONFIG_ACP2 */

	/* Clear BSS */
	memset((void *)&_bss_start, 0, (&_bss_end - &_bss_start));

	/* Re-Initialize the serial port (since BSS just got cleared). */
	serial_early_init();

	/*
	  Set up the board info, global data, and stack
	*/

	addr = CONFIG_SYS_MALLOC_BASE;
	addr -= sizeof( bd_t );
	bd = ( bd_t * ) addr;
	addr -= sizeof( gd_t );
	gd = ( gd_t * ) addr;
	addr -= 16;
	addr &= ~0xf;
	s = ( unsigned long * ) addr;
	* s -- = 0;
	* s -- = 0;
	addr = ( unsigned long ) s;
	__asm__ __volatile__( "" : : : "memory" );
	memset( ( void * ) gd, 0, sizeof( gd_t ) );
	gd->bd = bd;

	/*
	  Get the size of memory...
	*/

	gd->ram_size = ( 256 * 1024 * 1024 );
	bd->bi_memstart = 0;
	bd->bi_memsize = gd->ram_size;

	/* Set up the Stack */
	acp_mem_init(addr, 0, ( unsigned long ) acp_init_r);

	return;
}

/*
 * This is the next part if the initialization sequence: we are now
 * running from RAM and have a "normal" C environment, i. e. global
 * data can be written, BSS has been cleared, the stack size in not
 * that critical any more, etc.
 */
void board_init_r(gd_t *id, ulong dest_addr)
{
#ifndef CONFIG_ACP
	bd_t *bd;
	ulong malloc_start;

#ifndef CONFIG_SYS_NO_FLASH
	ulong flash_size;
#endif

	gd = id;		/* initialize RAM version of global data */
	bd = gd->bd;

	gd->flags |= GD_FLG_RELOC;	/* tell others: relocation done */

	/* The Malloc area is immediately below the monitor copy in DRAM */
	malloc_start = dest_addr - TOTAL_MALLOC_LEN;

#if defined(CONFIG_MPC85xx) || defined(CONFIG_MPC86xx)
	/*
	 * The gd->cpu pointer is set to an address in flash before relocation.
	 * We need to update it to point to the same CPU entry in RAM.
	 */
	gd->cpu += dest_addr - CONFIG_SYS_MONITOR_BASE;

	/*
	 * If we didn't know the cpu mask & # cores, we can save them of
	 * now rather than 'computing' them constantly
	 */
	fixup_cpu();
#endif

#ifdef CONFIG_SYS_EXTRA_ENV_RELOC
	/*
	 * Some systems need to relocate the env_addr pointer early because the
	 * location it points to will get invalidated before env_relocate is
	 * called.  One example is on systems that might use a L2 or L3 cache
	 * in SRAM mode and initialize that cache from SRAM mode back to being
	 * a cache in cpu_init_r.
	 */
	gd->env_addr += dest_addr - CONFIG_SYS_MONITOR_BASE;
#endif

	serial_initialize();

	debug("Now running in RAM - U-Boot at: %08lx\n", dest_addr);

	WATCHDOG_RESET();

	/*
	 * Setup trap handlers
	 */
	trap_init(dest_addr);

#ifdef CONFIG_ADDR_MAP
	init_addr_map();
#endif

#if defined(CONFIG_BOARD_EARLY_INIT_R)
	board_early_init_r();
#endif

	monitor_flash_len = (ulong)&__init_end - dest_addr;

	WATCHDOG_RESET();

#ifdef CONFIG_LOGBUFFER
	logbuff_init_ptrs();
#endif
#ifdef CONFIG_POST
	post_output_backlog();
#endif

	WATCHDOG_RESET();

#if defined(CONFIG_SYS_DELAYED_ICACHE)
	icache_enable();	/* it's time to enable the instruction cache */
#endif

#if defined(CONFIG_SYS_INIT_RAM_LOCK) && defined(CONFIG_E500)
	unlock_ram_in_cache();	/* it's time to unlock D-cache in e500 */
#endif

#if defined(CONFIG_PCI) && defined(CONFIG_SYS_EARLY_PCI_INIT)
	/*
	 * Do early PCI configuration _before_ the flash gets initialised,
	 * because PCU ressources are crucial for flash access on some boards.
	 */
	pci_init();
#endif
#if defined(CONFIG_WINBOND_83C553)
	/*
	 * Initialise the ISA bridge
	 */
	initialise_w83c553f();
#endif

	asm("sync ; isync");

	mem_malloc_init(malloc_start, TOTAL_MALLOC_LEN);

#if !defined(CONFIG_SYS_NO_FLASH)
	puts("Flash: ");

	if (board_flash_wp_on()) {
		printf("Uninitialized - Write Protect On\n");
		/* Since WP is on, we can't find real size.  Set to 0 */
		flash_size = 0;
	} else if ((flash_size = flash_init()) > 0) {
#ifdef CONFIG_SYS_FLASH_CHECKSUM
		print_size(flash_size, "");
		/*
		 * Compute and print flash CRC if flashchecksum is set to 'y'
		 *
		 * NOTE: Maybe we should add some WATCHDOG_RESET()? XXX
		 */
		if (getenv_yesno("flashchecksum") == 1) {
			printf("  CRC: %08X",
			       crc32(0,
				     (const unsigned char *)
				     CONFIG_SYS_FLASH_BASE, flash_size)
				);
		}
		putc('\n');
#else  /* !CONFIG_SYS_FLASH_CHECKSUM */
		print_size(flash_size, "\n");
#endif /* CONFIG_SYS_FLASH_CHECKSUM */
	} else {
		puts(failed);
		hang();
	}

	/* update start of FLASH memory    */
	bd->bi_flashstart = CONFIG_SYS_FLASH_BASE;
	/* size of FLASH memory (final value) */
	bd->bi_flashsize = flash_size;

#if defined(CONFIG_SYS_UPDATE_FLASH_SIZE)
	/* Make a update of the Memctrl. */
	update_flash_size(flash_size);
#endif


#if defined(CONFIG_OXC) || defined(CONFIG_RMU)
	/* flash mapped at end of memory map */
	bd->bi_flashoffset = CONFIG_SYS_TEXT_BASE + flash_size;
#elif CONFIG_SYS_MONITOR_BASE == CONFIG_SYS_FLASH_BASE
	bd->bi_flashoffset = monitor_flash_len;	/* reserved area for monitor */
#endif
#endif /* !CONFIG_SYS_NO_FLASH */

	WATCHDOG_RESET();

	/* initialize higher level parts of CPU like time base and timers */
	cpu_init_r();

	WATCHDOG_RESET();

#ifdef CONFIG_SPI
#if !defined(CONFIG_ENV_IS_IN_EEPROM)
	spi_init_f();
#endif
	spi_init_r();
#endif

#if defined(CONFIG_CMD_NAND)
	WATCHDOG_RESET();
	puts("NAND:  ");
	nand_init();		/* go init the NAND */
#endif

#ifdef CONFIG_GENERIC_MMC
/*
 * MMC initialization is called before relocating env.
 * Thus It is required that operations like pin multiplexer
 * be put in board_init.
 */
	WATCHDOG_RESET();
	puts("MMC:  ");
	mmc_initialize(bd);
#endif

	/* relocate environment function pointers etc. */
	env_relocate();

	/*
	 * after non-volatile devices & environment is setup and cpu code have
	 * another round to deal with any initialization that might require
	 * full access to the environment or loading of some image (firmware)
	 * from a non-volatile device
	 */
	cpu_secondary_init_r();

	/*
	 * Fill in missing fields of bd_info.
	 * We do this here, where we have "normal" access to the
	 * environment; we used to do this still running from ROM,
	 * where had to use getenv_f(), which can be pretty slow when
	 * the environment is in EEPROM.
	 */

#if defined(CONFIG_SYS_EXTBDINFO)
#if defined(CONFIG_405GP) || defined(CONFIG_405EP)
#if defined(CONFIG_I2CFAST)
	/*
	 * set bi_iic_fast for linux taking environment variable
	 * "i2cfast" into account
	 */
	{
		if (getenv_yesno("i2cfast") == 1) {
			bd->bi_iic_fast[0] = 1;
			bd->bi_iic_fast[1] = 1;
		}
	}
#endif /* CONFIG_I2CFAST */
#endif /* CONFIG_405GP, CONFIG_405EP */
#endif /* CONFIG_SYS_EXTBDINFO */

#if defined(CONFIG_SC3)
	sc3_read_eeprom();
#endif

#if defined(CONFIG_ID_EEPROM) || defined(CONFIG_SYS_I2C_MAC_OFFSET)
	mac_read_from_eeprom();
#endif

#ifdef	CONFIG_HERMES
	if ((gd->board_type >> 16) == 2)
		bd->bi_ethspeed = gd->board_type & 0xFFFF;
	else
		bd->bi_ethspeed = 0xFFFF;
#endif

#ifdef CONFIG_CMD_NET
	/* kept around for legacy kernels only ... ignore the next section */
	eth_getenv_enetaddr("ethaddr", bd->bi_enetaddr);
#ifdef CONFIG_HAS_ETH1
	eth_getenv_enetaddr("eth1addr", bd->bi_enet1addr);
#endif
#ifdef CONFIG_HAS_ETH2
	eth_getenv_enetaddr("eth2addr", bd->bi_enet2addr);
#endif
#ifdef CONFIG_HAS_ETH3
	eth_getenv_enetaddr("eth3addr", bd->bi_enet3addr);
#endif
#ifdef CONFIG_HAS_ETH4
	eth_getenv_enetaddr("eth4addr", bd->bi_enet4addr);
#endif
#ifdef CONFIG_HAS_ETH5
	eth_getenv_enetaddr("eth5addr", bd->bi_enet5addr);
#endif
#endif /* CONFIG_CMD_NET */

	WATCHDOG_RESET();

#if defined(CONFIG_PCI) && !defined(CONFIG_SYS_EARLY_PCI_INIT)
	/*
	 * Do pci configuration
	 */
	pci_init();
#endif

/** leave this here (after malloc(), environment and PCI are working) **/
	/* Initialize stdio devices */
	stdio_init();

	/* Initialize the jump table for applications */
	jumptable_init();

#if defined(CONFIG_API)
	/* Initialize API */
	api_init();
#endif

	/* Initialize the console (after the relocation and devices init) */
	console_init_r();

#if defined(CONFIG_MISC_INIT_R)
	/* miscellaneous platform dependent initialisations */
	misc_init_r();
#endif

#ifdef	CONFIG_HERMES
	if (bd->bi_ethspeed != 0xFFFF)
		hermes_start_lxt980((int) bd->bi_ethspeed);
#endif

#if defined(CONFIG_CMD_KGDB)
	WATCHDOG_RESET();
	puts("KGDB:  ");
	kgdb_init();
#endif

	debug("U-Boot relocated to %08lx\n", dest_addr);

	/*
	 * Enable Interrupts
	 */
	interrupt_init();

#if defined(CONFIG_STATUS_LED) && defined(STATUS_LED_BOOT)
	status_led_set(STATUS_LED_BOOT, STATUS_LED_BLINKING);
#endif

	udelay(20);

	/* Initialize from environment */
	load_addr = getenv_ulong("loadaddr", 16, load_addr);

	WATCHDOG_RESET();

#if defined(CONFIG_CMD_SCSI)
	WATCHDOG_RESET();
	puts("SCSI:  ");
	scsi_init();
#endif

#if defined(CONFIG_CMD_DOC)
	WATCHDOG_RESET();
	puts("DOC:   ");
	doc_init();
#endif

#ifdef CONFIG_BITBANGMII
	bb_miiphy_init();
#endif
#if defined(CONFIG_CMD_NET)
	WATCHDOG_RESET();
	puts("Net:   ");
	eth_initialize(bd);
#endif

#if defined(CONFIG_CMD_NET) && defined(CONFIG_RESET_PHY_R)
	WATCHDOG_RESET();
	debug("Reset Ethernet PHY\n");
	reset_phy();
#endif

#ifdef CONFIG_POST
	post_run(NULL, POST_RAM | post_bootmode_get(0));
#endif

#if defined(CONFIG_CMD_PCMCIA) \
    && !defined(CONFIG_CMD_IDE)
	WATCHDOG_RESET();
	puts("PCMCIA:");
	pcmcia_init();
#endif

#if defined(CONFIG_CMD_IDE)
	WATCHDOG_RESET();
#ifdef	CONFIG_IDE_8xx_PCCARD
	puts("PCMCIA:");
#else
	puts("IDE:   ");
#endif
#if defined(CONFIG_START_IDE)
	if (board_start_ide())
		ide_init();
#else
	ide_init();
#endif
#endif

#ifdef CONFIG_LAST_STAGE_INIT
	WATCHDOG_RESET();
	/*
	 * Some parts can be only initialized if all others (like
	 * Interrupts) are up and running (i.e. the PC-style ISA
	 * keyboard).
	 */
	last_stage_init();
#endif

#if defined(CONFIG_CMD_BEDBUG)
	WATCHDOG_RESET();
	bedbug_init();
#endif

#if defined(CONFIG_PRAM) || defined(CONFIG_LOGBUFFER)
	/*
	 * Export available size of memory for Linux,
	 * taking into account the protected RAM at top of memory
	 */
	{
		ulong pram = 0;
		char memsz[32];

#ifdef CONFIG_PRAM
		pram = getenv_ulong("pram", 10, CONFIG_PRAM);
#endif
#ifdef CONFIG_LOGBUFFER
#ifndef CONFIG_ALT_LB_ADDR
		/* Also take the logbuffer into account (pram is in kB) */
		pram += (LOGBUFF_LEN + LOGBUFF_OVERHEAD) / 1024;
#endif
#endif
		sprintf(memsz, "%ldk", (bd->bi_memsize / 1024) - pram);
		setenv("mem", memsz);
	}
#endif

#ifdef CONFIG_PS2KBD
	puts("PS/2:  ");
	kbd_init();
#endif

#ifdef CONFIG_MODEM_SUPPORT
	{
		extern int do_mdm_init;

		do_mdm_init = gd->do_mdm_init;
	}
#endif

	/* Initialization complete - start the monitor */

	/* main_loop() can return to retry autoboot, if so just run it again. */
	for (;;) {
		WATCHDOG_RESET();
		main_loop();
	}

	/* NOTREACHED - no way out of command loop except booting */
#endif /* CONFIG_ACP */
}

/*
  ----------------------------------------------------------------------
  acp_init_r

  ACP late initialization routine.
*/

void nic_loopback_test( void );
volatile uchar * PktBuf;

void
acp_init_r( void )
{
	bd_t *bd;
	int core;
	int group;
	unsigned long cold_start;
	unsigned char *buf;
#if defined(ACP_25xx) && !defined(ACP_ISS) && defined(CONFIG_ACP2)
	unsigned long *phyRegs = (unsigned long *)CANNED_PHY_REGS_ADDRESS;
#endif

	bd = gd->bd;

	__asm__ __volatile__ ("mfspr %0,0x11e" : "=r" (core));

#if defined(ACP_25xx) && !defined(ACP_EMU)
	cold_start = dcr_read(DCR_RESET_BASE + 0xe) & 0xf;
	cold_start |= dcr_read(DCR_RESET_BASE + 0x8) & 0x3;
	cold_start |= dcr_read(DCR_RESET_BASE + 0x6) & 0x3;
	cold_start = (0 != cold_start);
#else
	cold_start = (0 != (0x00ffe000 & dcr_read((DCR_RESET_BASE + 1))));
#endif

	/*
	  Enable Machine Checks.
	*/

	{
		unsigned long value;

		__asm__ __volatile__ ("mfspr %0,0x23c" : "=r" (value));
		__asm__ __volatile__ ("mtspr 0x33c,%0" : : "r" (value));	
		__asm__ __volatile__ ("mfmsr %0" : "=r" (value));
		value |= 0x1000;
		__asm__ __volatile__ ("mtmsr %0" : : "r" (value));
	}

	/* Set up memory allocation. */
	mem_malloc_init(CONFIG_SYS_MALLOC_BASE, CONFIG_SYS_MALLOC_SIZE);

	/* Set up the environment */
	if( 0 != env_init( ) ) {
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
	}
	
	/* Set up the time base */
	if( 0 != init_timebase( ) ) {
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
	}

#ifdef CONFIG_ACP2
	if( ( volatile uchar * ) 0 == 
	    ( PktBuf = ( volatile uchar * )
	      malloc( (PKTBUFSRX+1) * PKTSIZE_ALIGN + PKTALIGN ) ) ) {
	  printf( "%s:%s:%d - malloc() failed!\n",
		  __FILE__, __FUNCTION__, __LINE__ );
	}
#endif

	/*
	  Initialize MDIO
	*/
#ifndef ACP_ISS
	mdio_initialize( );
#ifndef CONFIG_ACP2
	i2c_init(CONFIG_SYS_I2C_SPEED, 0);
#endif
#endif

#ifdef ACP_25xx
	/*
	  On the 2500, IO pins get shared.  To use the FEMAC, the pins
	  must be connected.  So, connect the pins.
	*/
	writel(0x0c0c0c0c, 0xf0801064);
	writel(0x180c0c0c, 0xf0801068);
	writel(0x04181818, 0xf0801074);
	writel(0x18181800, 0xf0801078);
	writel(0x00180070, 0xf0801060);
#endif

	/* NAND */
#if defined(CONFIG_LSI_NAND)
	nand_init( );
#endif
	env_relocate( );

	printf("Updating the Environment...\n");	/* ZZZ */

	/* Update "baudrate" now that the environment is available. */
	{
		char *env_baudrate;

		env_baudrate = getenv("baudrate");

		if ((char *)0 == env_baudrate) {
			gd->baudrate = CONFIG_BAUDRATE;
		} else {
			gd->baudrate = simple_strtoul(env_baudrate, NULL, 10);
		}
	}

	/*
	  Update the environment, if needed.
	*/

#ifndef ACP_ISS
	{
		int env_save = 0;
		char * env_value;
		unsigned long temp;
		char buffer [ 80 ];

#ifdef CONFIG_ACP2
		env_value = getenv( "memory" );
		sprintf( buffer, "%d", 1 << ( sysmem_size - 20 ) );

		if( ( char * ) 0 == env_value ||
		    0 != strcmp( env_value, buffer ) ) {
			setenv( "memory", buffer );
			env_save = 1;
		}

		env_value = getenv( "version2" );
		strcpy( buffer, get_lsi_version( ) );

		if( ( char * ) 0 == env_value ||
		    0 != strcmp( env_value, buffer ) ) {
			setenv( "version2", buffer );
			env_save = 1;
		}

#if defined(ACP_25xx)

		/*
		 * check if LCM has an updated set of sysmem PHY registers
		 * that need to be stored 
		 */
#define SECTOR_SIZE 0x10000
#define SECTOR_BASE_ADDR(n) ( SECTOR_SIZE * (n) )

		ssp_init(0, 0);
		if (*phyRegs == CANNED_PHY_REGS_TAG_SAVE) {
			unsigned long *pCRC;
			/* TODO : make sure sysmem really works!! */

			/* write to PROM/FLASH */
			*phyRegs = CANNED_PHY_REGS_TAG_PROM;

			buf = malloc(SECTOR_SIZE);
			if (buf == 0) {
				printf("malloc failed - "
				       "couldn't write PHY regs\n");
				return;
			}

			printf("writing sysmem PHY regs to PROM!\n");
			/*
			  read the second sector (where u-boot parameters lives)
			*/
			ssp_read(buf, SECTOR_BASE_ADDR(1),  SECTOR_SIZE);
			memcpy(&buf[0xfe00],
			       (const void *)CANNED_PHY_REGS_ADDRESS, 464);

			pCRC = (unsigned long *) &buf[0xfff4];
			*pCRC = crc32(0, &buf[0xfc00], 1012);

			ssp_write(buf, SECTOR_BASE_ADDR(1), SECTOR_SIZE, 1);

		}
#endif
#else
		env_value = getenv( "version3" );
		strcpy( buffer, get_lsi_version( ) );

		if( ( char * ) 0 == env_value ||
		    0 != strcmp( env_value, buffer ) ) {
			setenv( "version3", buffer );
			env_save = 1;
		}

		if (cold_start) {
			int rc;

			rc = acp_osg_readenv();

			if (-1 == rc)
				acp_failure(__FILE__, __FUNCTION__, __LINE__);

			if (1 == rc)
				env_save = 1;
		}

		/* Set the PLB6 hang pulse count. */
		env_value = getenv("plb6_hpc");

		if ((char *)0 == env_value) {
			temp = 0x1000;
			sprintf(buffer, "0x%lx", temp);
			setenv("plb6_hpc", buffer);
			env_save = 1;
		} else {
			temp = simple_strtoul(env_value, NULL, 0);
		}

		dcr_write(temp, 0x10d);
		dcr_write(0xffffffff, 0x10e);
		dcr_write(0xffffffff, 0x10f);
		dcr_write(0xffffffff, 0x110);

		/* Set the PLB6 paam value. */
		env_value = getenv("plb6_paam");

		if ((char *)0 == env_value) {
			temp = 1;
			sprintf(buffer, "%lu", temp);
			setenv("plb6_paam", buffer);
			env_save = 1;
		} else {
			temp = simple_strtoul(env_value, NULL, 0);
		}

		dcr_write((temp << 30), 0x103);
#endif

		if (0 != env_save)
			saveenv();
	}
#endif

#ifdef CONFIG_ACP3
	/* Set the FDT address to the builtin flattened device tree. */
	working_fdt = (struct fdt_header *)get_acp_fdt(acp_osg_get_group(core));
#endif /* CONFIG_ACP3 */

	interrupt_init();

#ifdef CONFIG_ACP3
	/* Clear the Reset Status Register. */
#ifdef ACP_25xx
	dcr_write(0xf, (DCR_RESET_BASE + 0xe));
	dcr_write(0x3, (DCR_RESET_BASE + 0x8));
	dcr_write(0x3, (DCR_RESET_BASE + 0x6));
#else
	dcr_write(0xffffe000, (DCR_RESET_BASE + 1));
#endif

	/*
	  If this is the initial boot, bring up the other OS boot cores.

	  In all cases, bring up the secondary cores associated with
	  this OS group.
	*/

	printf("Bringing Up Other Cores...\n");	/* ZZZ */

	{
		int i;
		char *testmode;

		/*
		  Core 0 has to have access to the memory of every group...
		*/
		for (i = 0; i < ACP_MAX_OS_GROUPS; ++i) {
			if (-1 == acp_osg_map(i))
				acp_failure(__FILE__, __FUNCTION__, __LINE__);
		}

		for (i = 0; i < ACP_NR_CORES; ++i) {
			int group;
			unsigned long os_base;
			unsigned long cores;

			if (i == core)
				continue;

			if (-1 == (group = acp_osg_get_group(i)))
				continue;

			cores = acp_osg_group_get_res(group, ACP_OS_CORES);

			if (0 == (cores & (1 << i)))
				continue;

			if (acp_osg_is_boot_core(i) && cold_start) {
				dcr_write((1 << i), 0xffc00040);
			} else {
				os_base =
					(acp_osg_group_get_res(group,
							       ACP_OS_BASE) *
					 1024 * 1024);
				acp_spintable_init(i, cold_start, os_base);
			}
		}

		testmode = getenv("testmode");

		if (((char *)0 != testmode) && (0 == strcmp("on", testmode))) {
			printf("Test Mode: Spintables at 0x%x 0x%x 0x%x\n",
			       (unsigned int)acp_spintable[1],
			       (unsigned int)acp_spintable[2],
			       (unsigned int)acp_spintable[3]);
		}
	}

	/* Update the device trees for all groups. */
	if (0 != acp_osg_initialize())
		acp_failure(__FILE__, __FUNCTION__, __LINE__);
#endif

	eth_initialize(bd);
	serial_init();
	acp_splash();

#if defined(ACP_25xx) && defined(CONFIG_ACP2)
	{
		int rc;
		unsigned long ncp_denali_ctl_20;
		unsigned long ncp_denali_ctl_31;
		unsigned long debug;
		unsigned long system_pll;
		unsigned long ppc_pll;
		unsigned long ddr_pll;
		unsigned long peripheral_clock;
		unsigned long l2_0_sleep_state;
		unsigned long l2_1_sleep_state;

		ncr_read32(NCP_REGION_ID(0x22, 0), 0x50, &ncp_denali_ctl_20);
		ncr_read32(NCP_REGION_ID(0x22, 0), 0x7c, &ncp_denali_ctl_31);
		ncr_read32(NCP_REGION_ID(0x20, 0), 0x100, &debug);

		dcr_write(0x80, 0x300);
		l2_0_sleep_state = dcr_read(0x304);
		dcr_write(0x80, 0x400);
		l2_1_sleep_state = dcr_read(0x404);

		printf("--------------- AXM2500 Settings ---------------\n"
		       "               L2 State: %d %d\n"
		       "   Reset instead of IPI: %s\n"
		       "                    ECC: %s\n"
		       "                 Memory: %s\n"
		       "               SysCache: %s\n"
		       "                  Reset: %s\n"
#ifdef NCP_SM_PHY_REG_RESTORE
		       "SM PHY Register Restore: %s\n"
#endif
		       "         PCIe Test Mode: %s\n\n",
		       l2_0_sleep_state, l2_1_sleep_state,
#ifdef RESET_INSTEAD_OF_IPI
		       "Enabled",
#else
		       "Disabled",
#endif
		       (0x300 ==
			(ncp_denali_ctl_20 & 0x300)) ? "On" : "Off",
		       (0x300 ==
			(ncp_denali_ctl_31 & 0x300)) ? "Dual" : "Single",
		       (0x1 ==
			(debug & 0x1)) ? "Disabled" : "Enabled",
		       (0 == reset_enabled) ? "Disabled" : "Enabled",
#ifdef NCP_SM_PHY_REG_RESTORE
		       (0 == ncp_sm_phy_reg_restore) ? "Disabled" : "Enabled",
#endif
#ifdef ACP2_PCIE_TEST
		       "Enabled"
#else
		       "Disabled"
#endif
		       );

		rc = acp_clock_get(clock_sys, &system_pll);
		rc |= acp_clock_get(clock_ppc, &ppc_pll);
		rc |= acp_clock_get(clock_ddr, &ddr_pll);
		rc |= acp_clock_get(clock_peripheral, &peripheral_clock);

		if (0 != rc)
			printf("Error Getting PLL/Clock Frequencies!\n");
		else
			printf("      System PLL: %04d MHz\n"
			       "         PPC PLL: %04d MHz\n"
			       "         DDR PLL: %04d MHz\n"
			       "Peripheral Clock: %04d MHz\n\n",
			       system_pll / 1000,
			       ppc_pll / 1000,
			       ddr_pll / 2000,
			       peripheral_clock / 1000);
	}
#endif

#if defined(CONFIG_ACP2) || defined(CONFIG_ACP3)
	/*
	  Only set up PCI when in internal boot mode, in control of
	  one of the PEIs, and the root complex.
	*/

	{	
		int boot_mode;
		unsigned long control;
		int pci_rc = 0;
		int group;
		int pei_mask = 0;

#if defined(CONFIG_ACP3)	
		group = acp_osg_get_group(core);
#endif

#if defined(ACP_25xx)
		control = dcr_read(0xd0f);
		boot_mode = (control & 0x100) >> 8;
		if (0 != ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &control)) {
			printf("Error Reading PHY Control: "
			       "Skipping PCI setup.\n");
			control = 0;
		}

#if defined (CONFIG_ACP2)
		if (0 != (control & 0x00400000))
			pci_rc = 1;
		if (0 != (control & 0x00080000))
			pci_rc = 1;
#elif defined (CONFIG_ACP3)
		if (0 != (control & 0x00400000) 
			&& 0 != acp_osg_group_get_res(group, ACP_OS_PCIE0)) {
			pci_rc = 1;
			pei_mask |= 1;
		}

		if (0 != (control & 0x00080000) &&
		    0 != acp_osg_group_get_res(group, ACP_OS_PCIE1)) {
			pci_rc = 1;
			pei_mask |= 2;
		}
#endif
#else
#if defined (CONFIG_ACP3)
		control = dcr_read(DCR_RESET_BASE);
		boot_mode = (control & 0x80000000) >> 31;
		control = readl((void *)GPREG_PHY_CTRL0);

		if (0 != (control & 0x1000) &&
		    0 != acp_osg_group_get_res(group, ACP_OS_PCIE0)) {
			pci_rc = 1;
			pei_mask |= 1;
		}
#endif
#endif

		if (0 == boot_mode && 1 == pci_rc) {
#if defined(ACP_25xx) && defined(CONFIG_ACP2)
			{
				char * env_value;
				unsigned long pciStatus, linkState;
				
				pciStatus = readl((void *)(PCIE0_CONFIG + 0x1004));
				printk("PEI0 pciStatus = 0x%x\n", pciStatus);
				linkState = (pciStatus & 0x3f00) >> 8;
				if (linkState == 0xb) {
					printf("PCIE0 link State UP = 0x%x\n", linkState);
					env_value = getenv("pei0_speed");
					if ((char *)0 != env_value) {
						unsigned long pei0_speed;

						pei0_speed = simple_strtoul(env_value, NULL, 0);
						pci_speed_change(0, pei0_speed);
					}
				} else {
					printf("PCIE0 link State DOWN = 0x%x\n", linkState);
				}
				pciStatus = readl((void *)(PCIE1_CONFIG + 0x1004));
				printk("PEI1 pciStatus = 0x%x\n", pciStatus);
				linkState = (pciStatus & 0x3f00) >> 8;
	
				if (linkState == 0xb) {
					printf("PCIE1 link State UP = 0x%x\n", linkState);
					env_value = getenv("pei1_speed");
					if ((char *)0 != env_value) {
						unsigned long pei1_speed; 
					
						pei1_speed = simple_strtoul(env_value, NULL, 0); 
						pci_speed_change(1, pei1_speed);
					}
				} else {
					printf("PCIE1 link State DOWN = 0x%x\n", linkState);
				}
			}
#endif
#if defined(CONFIG_ACP3) && defined(CONFIG_PCI)
				pci_init_board();
#endif
		}
	}
#endif

#if 0
	/* Display the Part Information. */

	/*
	  Here's how the RTE does it...

	  1, 3, 4, or 5 => ACP344x
	  2             => ACP342x
	  6             => ACP25xx
	*/

	{
		unsigned long value0;
		unsigned long value1;

		ncr_read32(NCP_REGION_ID(0xa, 0x10), 0x2c, &value0);
	
		switch (value0 & 0x1f) {
		case 0:
			printf("ACP3448V1\n");
			break;
		case 1:
			printf("ACP3448V2\n");
			break;
		case 2:
			ncr_read32(NCP_REGION_ID(0xa, 0x10), 0x20, &value1);

			switch ((value1 & 0xf0000000) >> 28) {
			case 0:
				printf("ACP3421C\n");
				break;
			case 1:
				printf("ACP3421D\n");
				break;
			default:
				printf("ACP3421 Unexpected PackageType 0x%x\n",
				       (value1 & 0xf0000000) >> 28);
				break;
			}
			break;
		case 3:
			printf("ACP3442\n");
			break;
		case 4:
			printf("ACP3440\n");
			break;
		case 5:
			printf("ACP2500\n");
			break;
		default:
			printf("Unknown chipType 0x%x\n", value0 & 0x1f);
			break;
		}
	}
#endif

#if 0
	{
		unsigned long core_pvr;

		__asm__ __volatile__ ("mfspr %0,0x11f" : "=r" (core_pvr));
		printf("PVR:0x%lx\n", core_pvr);
	}
#endif

#ifndef ACP_ISS
	printf( "System Memory Size: %lu M\n", get_sysmem_size( ) );
#endif
	printf( "LSI Version: %s\n", get_lsi_version( ) );

	/*ZZZ*/
#if 0
	{
		unsigned long pvr_value;
		unsigned long dbcr0_value;

		__asm__ __volatile__ ("mfspr %0,0x11f" : "=r" (pvr_value));
		__asm__ __volatile__ ("mfspr %0,0x134" : "=r" (dbcr0_value));

		printf("** PVR: 0x%08x  DBCR0: 0x%08x\n",
		       pvr_value, dbcr0_value);
	}
#endif
	/*ZZZ*/
	       

	/* IP Address */
	/*gd->bd->bi_ip_addr = getenv_IPaddr ("ipaddr");*/

#ifdef CONFIG_ACP3
	/*
	  Configure jumptable to allow standalone programs access to
	  some functions.
	*/
 	jumptable_init();
#endif

	/*ZZZ*/
#if 0
#define BURST_ADDRESS 0x400000
#define BURST_SIZE 32
	{
		unsigned char *burst = (unsigned char *)BURST_ADDRESS;
		unsigned char value = 0x01;
		int i;
		int iteration = 1;

		/* A New Memory Test... */
		printf("Starting the fake coarse write-leveling test.\n"
		       "Ctrl-C to Stop the Test and Continue Booting...\n");

		for (;;) {
			/* Write the current value. */
			for (i = 0; i < BURST_SIZE; i += 2)
				burst[i] = value;

			/* Read back and verify. */
			for (i = 0; i < BURST_SIZE; i += 2) {
				unsigned char compare;

				compare = burst[i];

				if (value != compare)
					printf("ERROR: iteration %d i %d "
					       "wrote 0x%02x read 0x%02x\n",
					       iteration, i, value, compare);
			}

			/* Change the value. */
			if (0x80 > value)
				value = value << 1;
			else
				value = 0x01;

			/* Check for Ctrl-C. */
			if (ctrlc())
				break;

			++iteration;
		}

		printf("\nEnding the test after %d iterations.\n", iteration);
	}
#endif
	/*ZZZ*/

	/* Jump to the main loop... */
	for (;;) {
		main_loop();
	}

	return;

}

void hang(void)
{
	puts("### ERROR ### Please RESET the board ###\n");
	bootstage_error(BOOTSTAGE_ID_NEED_RESET);
	for (;;)
		;
}


#if 0	/* We could use plain global data, but the resulting code is bigger */
/*
 * Pointer to initial global data area
 *
 * Here we initialize it.
 */
#undef	XTRN_DECLARE_GLOBAL_DATA_PTR
#define XTRN_DECLARE_GLOBAL_DATA_PTR	/* empty = allocate here */
DECLARE_GLOBAL_DATA_PTR =
	(gd_t *) (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_GBL_DATA_OFFSET);
#endif /* 0 */

/************************************************************************/
