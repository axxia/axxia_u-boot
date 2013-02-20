/*
 * boot-spl.c
 *
 * Axxia boot code for spl builds.
 *
 * Copyright (C) 2013 LSI Corporation
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

#include <common.h>

void acp_mem_init(unsigned long, unsigned long, unsigned long);
void axxia_init_r(void);
extern unsigned long sysmem_size;

/*
  ==============================================================================
  ==============================================================================
  Private
  ==============================================================================
  ==============================================================================
*/

DECLARE_GLOBAL_DATA_PTR;

/*
  ==============================================================================
  ==============================================================================
  Public
  ==============================================================================
  ==============================================================================
*/

/*
  ------------------------------------------------------------------------------
  spl_boot_device
*/

unsigned long
spl_boot_device(void)
{
	return 0;
}

/*
  ------------------------------------------------------------------------------
  spl_display_print
*/

void
spl_display_print(void)
{
	return;
}

/*
  ------------------------------------------------------------------------------
  axxia_init_f

  Axxia early initialization code, first C code...
*/

void
axxia_init_f(void)
{
	bd_t *bd;
	register unsigned long addr;
	unsigned long *s;
	unsigned long core;
#if !defined(ACP_25xx)
	unsigned long l2version;
	unsigned long l2revision;
#endif

#if defined(ACP_25xx) && defined(RESET_INSTEAD_OF_IPI)
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
	acp_mem_init(addr, 0, ( unsigned long ) axxia_init_r);

	/* Never reached. */
	return;
}

/*
  ------------------------------------------------------------------------------
  axxia_init_r

  Axxia initialization code.
*/

void
axxia_init_r(void)
{
	bd_t *bd;
	int core;
	int group;
	unsigned long cold_start;
	unsigned char *buf;
#if defined(ACP_25xx) && !defined(ACP_ISS)
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

	/* Set up the time base */
	if( 0 != init_timebase( ) ) {
		acp_failure( __FILE__, __FUNCTION__, __LINE__ );
	}

	/*
	  Initialize MDIO
	*/
#ifndef ACP_ISS
	mdio_initialize( );
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
	/*nand_init( );*/
#endif
	/*env_relocate( );*/

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

	interrupt_init();
	serial_init();

#if defined(ACP_25xx)
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

	printf( "System Memory Size: %lu M\n", get_sysmem_size( ) );
	printf( "LSI Version: %s\n", get_lsi_version( ) );

	return;
}
