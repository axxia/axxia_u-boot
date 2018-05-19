/*
 *  board/axxia/axc6700/secure.c
 *
 *  Copyright (C) 2015 Intel (john.jacques@intel.com)
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
 */

#include <config.h>
#include <common.h>
#include <version.h>
#include <serial.h>
#include <malloc.h>
#include <spl.h>
#include <asm/io.h>

/*
  ------------------------------------------------------------------------------
  setup_security
*/

int
setup_security(void)
{
	/*
	  Addresses...

	  0x170.1 - MMAP_SCB (0x8032000000)
	  0x171.1 - PERIPH_SCB (0x8080400000)
	  0x172.1 - PCI_SCB (0xa000400000)
	  0x173.1 - USB0_SCB (0x9000400000)
	  0x174.1 - USB1_SCB (0x9800400000)
	  0x1d2.0 - TZC (0x8005040000)
	*/

	/*
	  For now, allow access from anywhere, to anywhere with the
	  following exceptions: SCB and LSM.


	  write 0xFFFF to (@0x170.0x1.0x8) // [rni_security]
	  write 0xFFFF to (@0x170.0x1.0xc) // [trace_security]
	  write 0xFFFF to (@0x170.0x1.0x10) // [lsm_security]
	  write 0xFFFF to (@0x170.0x1.0x14) // [to_pci_security]
	  write 0xFFFF to (@0x170.0x1.0x18) // [nca_security]
	  write 0xFFFF to (@0x170.0x1.0x1c) // [axi2ser0_security]
	  write 0xFFFF to (@0x170.0x1.0x20) // [axi2ser1_security]
	  write 0xFFFF to (@0x170.0x1.0x24) // [axi2ser2_security]
	  write 0xFFFF to (@0x170.0x1.0x28) // [axi2ser3_security]
	  write 0xFFFF to (@0x170.0x1.0x2c) // [axi2ser4_security]
	  write 0xFFFF to (@0x170.0x1.0x30) // [axi2ser5_security]
	  write 0xFFFF to (@0x170.0x1.0x34) // [axi2ser6_security]
	  write 0xFFFF to (@0x170.0x1.0x38) // [axi2ser7_security]
	  write 0xFFFF to (@0x170.0x1.0x3c) // [axi2ser8_security]
	  write 0xFFFF to (@0x170.0x1.0x40) // [axi2ser9_security]
	  write 0xFFFF to (@0x170.0x1.0x44) // [axi2ser10_security]
	  write 0xFFFF to (@0x170.0x1.0x48) // [axi2ser11_security]
	  write 0xFFFF to (@0x170.0x1.0x4c) // [gpdmatzc_security]
	  write 0xFFFF to (@0x170.0x1.0x50) // [dapapb_security]
	  write 0xFFFF to (@0x170.0x1.0x54) // [gic500_security]
	  write 0xFFFF to (@0x170.0x1.0x58) // [scb_security]
	  write 0xFFFF to (@0x170.0x1.0x5c) // [to_usb0_security]
	  write 0xFFFF to (@0x170.0x1.0x60) // [to_usb1_security]
	  write 0xFFFF to (@0x170.0x1.0x64) // [gic490_security]
	  write 0xFFFF to (@0x170.0x1.0x68) // [trng_security]
	  write 0xFFFF to (@0x170.0x1.0x6c) // [awlock_security]
	  write 0xFFFF to (@0x170.0x1.0x70) // [sbb_security]
	  write 0xFFFF to (@0x170.0x1.0x74) // [pka_security]
	  write 0xFFFF to (@0x170.0x1.0x78) // [to_periph_security]
	  write 0xFFFF to (@0x170.0x1.0x7c) // [fes_security]

	  write 0xFFFFFFFF to (@0x170.0x1.0x800) // [axi2ser0_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x808) // [axi2ser0_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x810) // [axi2ser1_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x818) // [axi2ser1_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x820) // [axi2ser2_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x828) // [axi2ser2_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x830) // [axi2ser3_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x838) // [axi2ser3_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x840) // [axi2ser4_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x848) // [axi2ser4_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x850) // [axi2ser5_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x858) // [axi2ser5_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x860) // [axi2ser6_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x868) // [axi2ser6_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x870) // [axi2ser7_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x878) // [axi2ser7_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x880) // [axi2ser8_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x888) // [axi2ser8_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x890) // [axi2ser9_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x898) // [axi2ser9_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x8a0) // [axi2ser10_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x8a8) // [axi2ser10_wr_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x8b0) // [axi2ser11_rd_target_secure]
	  write 0xFFFFFFFF to (@0x170.0x1.0x8b8) // [axi2ser11_wr_target_secure]

	  write 0xFFFF to (@0x171.0x1.0x8) // [from_periph_security]
	  write 0xFFFF to (@0x171.0x1.0xc) // [miscapbp_security]
	  write 0xFFFF to (@0x171.0x1.0x10) // [sspuart_security]
	  write 0xFFFF to (@0x171.0x1.0x14) // [scb_security]
	  write 0xFFFF to (@0x171.0x1.0x18) // [i2c_security]
	  write 0xFFFF to (@0x171.0x1.0x1c) // [rom_security]
	  write 0xFFFF to (@0x171.0x1.0x20) // [gpio_security]

	  write 0xFFFF to (@0x172.0x1.0x8) // [pcie0_security]
	  write 0xFFFF to (@0x172.0x1.0xc) // [pciecfg0_security]
	  write 0xFFFF to (@0x172.0x1.0x10) // [apb_security]

	  write 0xFFFF to (@0x173.0x1.0xc) // [usb_security]
	  write 0xFFFF to (@0x173.0x1.0x10) // [gpreg_security]
	  write 0xFFFF to (@0x173.0x1.0x14) // [scb_security]

	  write 0xFFFF to (@0x174.0x1.0xc) // [usb_security]
	  write 0xFFFF to (@0x174.0x1.0x10) // [gpreg_security]
	  write 0xFFFF to (@0x174.0x1.0x14) // [scb_security]
	*/

	writel(0xffff, (MMAP_SCB + 0x08));
	writel(0xffff, (MMAP_SCB + 0x0c));
	writel(0xffff, (MMAP_SCB + 0x10));
	writel(0xffff, (MMAP_SCB + 0x14));
	writel(0xffff, (MMAP_SCB + 0x18));
	writel(0xffff, (MMAP_SCB + 0x1c));
	writel(0xffff, (MMAP_SCB + 0x20));
	writel(0xffff, (MMAP_SCB + 0x24));
	writel(0xffff, (MMAP_SCB + 0x28));
	writel(0xffff, (MMAP_SCB + 0x2c));
	writel(0xffff, (MMAP_SCB + 0x30));
	writel(0xffff, (MMAP_SCB + 0x34));
	writel(0xffff, (MMAP_SCB + 0x38));
	writel(0xffff, (MMAP_SCB + 0x3c));
	writel(0xffff, (MMAP_SCB + 0x40));
	writel(0xffff, (MMAP_SCB + 0x44));
	writel(0xffff, (MMAP_SCB + 0x48));
	writel(0xffff, (MMAP_SCB + 0x4c));
	writel(0xffff, (MMAP_SCB + 0x50));
	writel(0xffff, (MMAP_SCB + 0x54));
	writel(0xffff, (MMAP_SCB + 0x58));
	writel(0xffff, (MMAP_SCB + 0x5c));
	writel(0xffff, (MMAP_SCB + 0x60));
	writel(0xffff, (MMAP_SCB + 0x64));
	writel(0xffff, (MMAP_SCB + 0x68));
	writel(0xffff, (MMAP_SCB + 0x6c));
	writel(0xffff, (MMAP_SCB + 0x70));
	writel(0xffff, (MMAP_SCB + 0x74));
	writel(0xffff, (MMAP_SCB + 0x78));
	writel(0xffff, (MMAP_SCB + 0x7c));

	writel(0xffffffff, (MMAP_SCB + 0x800));
	writel(0xffffffff, (MMAP_SCB + 0x808));
	writel(0xffffffff, (MMAP_SCB + 0x810));
	writel(0xffffffff, (MMAP_SCB + 0x818));
	writel(0xffffffff, (MMAP_SCB + 0x820));
	writel(0xffffffff, (MMAP_SCB + 0x828));
	writel(0xffffffff, (MMAP_SCB + 0x830));
	writel(0xffffffff, (MMAP_SCB + 0x838));
	writel(0xffffffff, (MMAP_SCB + 0x840));
	writel(0xffffffff, (MMAP_SCB + 0x848));
	writel(0xffffffff, (MMAP_SCB + 0x850));
	writel(0xffffffff, (MMAP_SCB + 0x858));
	writel(0xffffffff, (MMAP_SCB + 0x860));
	writel(0xffffffff, (MMAP_SCB + 0x868));
	writel(0xffffffff, (MMAP_SCB + 0x870));
	writel(0xffffffff, (MMAP_SCB + 0x878));
	writel(0xffffffff, (MMAP_SCB + 0x880));
	writel(0xffffffff, (MMAP_SCB + 0x888));
	writel(0xffffffff, (MMAP_SCB + 0x890));
	writel(0xffffffff, (MMAP_SCB + 0x898));
	writel(0xffffffff, (MMAP_SCB + 0x8a0));
	writel(0xffffffff, (MMAP_SCB + 0x8a8));
	writel(0xffffffff, (MMAP_SCB + 0x8b0));
	writel(0xffffffff, (MMAP_SCB + 0x8b8));

	writel(0xffff, (PERIPH_SCB + 0x08));
	writel(0xffff, (PERIPH_SCB + 0x0c));
	writel(0xffff, (PERIPH_SCB + 0x10));
	writel(0xffff, (PERIPH_SCB + 0x14));
	writel(0xffff, (PERIPH_SCB + 0x18));
	writel(0xffff, (PERIPH_SCB + 0x1c));
	writel(0xffff, (PERIPH_SCB + 0x20));

#ifndef CONFIG_AXXIA_ANY_EMU

	writel(0xffff, (PCI_SCB + 0x08));
	writel(0xffff, (PCI_SCB + 0x0c));
	writel(0xffff, (PCI_SCB + 0x10));

	writel(0xffff, (USB0_SCB + 0x0c));
	writel(0xffff, (USB0_SCB + 0x10));
	writel(0xffff, (USB0_SCB + 0x14));

	writel(0xffff, (USB1_SCB + 0x0c));
	writel(0xffff, (USB1_SCB + 0x10));
	writel(0xffff, (USB1_SCB + 0x14));

#endif

#ifdef SYSCACHE_ONLY_MODE
        /*
          The RNI NIC-400 is currently configured to signal
          non-secured transactions only.  Override all transactions
          coming out of RNI as a SECURE. Use it only in a Secure
          state.
        */

        writel(0x2, (MMAP_SCB + 0x42800));
#endif

	/*
	  Set up the TZC
	*/

	/* Make sure the TZC has finished internal configuration. */
	(void)readl(TZC + 8);
	/* 0x1d2.0.0x8 = 0x1 */
	writel(0x1, (TZC + 0x8));
	/* 0x1d2.0.0x110 = 0xc000000f */
	writel(0xc000000f, (TZC + 0x110));
        /* 0x1d2.0.0x114 = 0xffffffff */
        writel(0xffffffff, (TZC + 0x114));

	return 0;
}
