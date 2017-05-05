/*
 * drivers/pci/pcie_axxia.c
 *
 * Copyright (C) 2017 Intel
 *
 * This program is free software;you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation;either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY;without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program;if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#define DEBUG

#include <common.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/types.h>
#include <pci.h>
#include <config.h>

/*
  The "LOS Work Around"
*/

#define ENABLE_LOS_WA

#define PEI_GENERAL_CORE_CTL_REG 0x38
#define PEI_SII_PWR_MGMT_REG 0xD4
#define PEI_SII_DBG_0_MON_REG 0xEC

#define PEI_SMLH_LINK_UP (0x1 << 12)
#define PEI_SMLH_LINK_STATE (0x3f << 4)
#define PEI_RDLH_LINK_UP (0x1 << 0)

/* Synopsis specific PCIE configuration registers */
#define PCIE_PORT_LINK_CONTROL          0x710
#define PORT_LINK_MODE_MASK             (0x3f << 16)
#define PORT_LINK_MODE_1_LANES          (0x1 << 16)
#define PORT_LINK_MODE_2_LANES          (0x3 << 16)
#define PORT_LINK_MODE_4_LANES          (0x7 << 16)
#define PORT_LINK_MODE_8_LANES          (0xf << 16)

#define PCIE_LINK_WIDTH_SPEED_CONTROL   0x80C
#define PORT_LOGIC_SPEED_CHANGE         (0x1 << 17)
#define PORT_LOGIC_LINK_WIDTH_MASK      (0x1f << 8)
#define PORT_LOGIC_LINK_WIDTH_1_LANES   (0x1 << 8)
#define PORT_LOGIC_LINK_WIDTH_2_LANES   (0x2 << 8)
#define PORT_LOGIC_LINK_WIDTH_4_LANES   (0x4 << 8)
#define PORT_LOGIC_LINK_WIDTH_8_LANES   (0x8 << 8)

#define PCIE_GEN3_EQ_CONTROL_OFF        0x8a8

#define PCIE_MSI_ADDR_LO                0x820
#define PCIE_MSI_ADDR_HI                0x824
#define PCIE_MSI_INTR0_ENABLE           0x828
#define PCIE_MSI_INTR0_MASK             0x82C
#define PCIE_MSI_INTR0_STATUS           0x830

#define PCIE_ATU_VIEWPORT               0x900
#define PCIE_ATU_REGION_INBOUND         (0x1 << 31)
#define PCIE_ATU_REGION_OUTBOUND        (0x0 << 31)
#define PCIE_ATU_REGION_INDEX3          (0x3 << 0)
#define PCIE_ATU_REGION_INDEX2          (0x2 << 0)
#define PCIE_ATU_REGION_INDEX1          (0x1 << 0)
#define PCIE_ATU_REGION_INDEX0          (0x0 << 0)
#define PCIE_ATU_CR1                    0x904
#define PCIE_ATU_TYPE_MEM               (0x0 << 0)
#define PCIE_ATU_TYPE_IO                (0x2 << 0)
#define PCIE_ATU_TYPE_CFG0              (0x4 << 0)
#define PCIE_ATU_TYPE_CFG1              (0x5 << 0)
#define PCIE_ATU_CR2                    0x908
#define PCIE_ATU_ENABLE                 (0x1 << 31)
#define PCIE_ATU_BAR_MODE_ENABLE        (0x1 << 30)
#define PCIE_ATU_LOWER_BASE             0x90C
#define PCIE_ATU_UPPER_BASE             0x910
#define PCIE_ATU_LIMIT                  0x914
#define PCIE_ATU_LOWER_TARGET           0x918
#define PCIE_ATU_BUS(x)                 (((x) & 0xff) << 24)
#define PCIE_ATU_DEV(x)                 (((x) & 0x1f) << 19)
#define PCIE_ATU_FUNC(x)                (((x) & 0x7) << 16)
#define PCIE_ATU_UPPER_TARGET           0x91C

#undef DEBUG_PCIE

#ifdef CONFIG_PCI

#define ACPX1_PCIE_MPAGE_UPPER(n) (0x1010 + (n * 8))
#define ACPX1_PCIE_MPAGE_LOWER(n) (0x1014 + (n * 8))

#define U64_TO_U32_LOW(val)     ((u32)((val) & 0x00000000ffffffffULL))
#define U64_TO_U32_HIGH(val)    ((u32)((val) >> 32))

#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

struct pci_hose_data {
	u64 dbi_base;
	u64 cc_gpreg_base;
	u64 axi_gpreg_base;
	u64 cfg0_base;
	u64 cfg1_base;
	u64 cfg0_size;
	u64 cfg1_size;
	u64 mem_mod_base;
	u64 mem_size;
	u64 mem_bus_addr;
	u64 io_mod_base;
	u64 io_size;
	u64 io_bus_addr;
	int lanes;
};

static struct pci_controller hose[CONFIG_SYS_PCIE_NR_PORTS];
static struct pci_hose_data hose_data[CONFIG_SYS_PCIE_NR_PORTS];

static inline void axxia_pcie_readl_rc(struct pci_controller *hose,
	u32 reg, u32 *val)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	*val = readl(data->dbi_base + reg);
}

static inline void axxia_pcie_writel_rc(struct pci_controller *hose,
	u32 val, u32 reg)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	writel(val, data->dbi_base + reg);
}

static inline void axxia_cc_gpreg_writel(struct pci_controller *hose,
	u32 val, u32 reg)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	writel(val, data->cc_gpreg_base + reg);
}

static inline void axxia_cc_gpreg_readl(struct pci_controller *hose,
	u32 reg, u32 *val)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	*val = readl(data->cc_gpreg_base + reg);
}
static inline void axxia_axi_gpreg_writel(struct pci_controller *hose,
	u32 val, u32 reg)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	writel(val, data->axi_gpreg_base + reg);
}

static inline void axxia_axi_gpreg_readl(struct pci_controller *hose,
	u32 reg, u32 *val)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	*val = readl(data->axi_gpreg_base + reg);
}

int axxia_pcie_cfg_read(void __iomem *addr, int where, int size, u32 *val)
{
	*val = readl(addr);

	if (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	else if (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;
	else if (size != 4)
		return 1;

	return 0;
}

int axxia_pcie_cfg_write(void __iomem *addr, int where, int size, u32 val)
{
	if (size == 4)
		writel(val, addr);
	else if (size == 2)
		writew(val, addr + (where & 2));
	else if (size == 1)
		writeb(val, addr + (where & 3));
	else
		return 1;
	return 0;
}
static void axxia_pcie_prog_viewport_cfg0(struct pci_controller *hose,
	u32 busdev)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	/* Program viewport 0 : OUTBOUND : CFG0 */
	axxia_pcie_writel_rc(hose,
			     PCIE_ATU_REGION_OUTBOUND
			     | PCIE_ATU_REGION_INDEX0, PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, data->cfg0_base, PCIE_ATU_LOWER_BASE);
#if defined(CONFIG_AXXIA_ANY_XLF)
	axxia_pcie_writel_rc(hose, (data->cfg0_base >> 32),
			     PCIE_ATU_UPPER_BASE);
#endif
	axxia_pcie_writel_rc(hose, data->cfg0_base + data->cfg0_size - 1,
			     PCIE_ATU_LIMIT);
	axxia_pcie_writel_rc(hose, busdev, PCIE_ATU_LOWER_TARGET);
	axxia_pcie_writel_rc(hose, 0, PCIE_ATU_UPPER_TARGET);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_CFG0, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, PCIE_ATU_ENABLE, PCIE_ATU_CR2);
}

static void axxia_pcie_prog_viewport_cfg1(struct pci_controller *hose,
	u32 busdev)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	/* Program viewport 1 : OUTBOUND : CFG1 */
	axxia_pcie_writel_rc(hose,
			     PCIE_ATU_REGION_OUTBOUND | PCIE_ATU_REGION_INDEX1,
			     PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_CFG1, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, data->cfg1_base, PCIE_ATU_LOWER_BASE);
#if defined(CONFIG_AXXIA_ANY_XLF)
	axxia_pcie_writel_rc(hose, (data->cfg1_base >> 32),
			     PCIE_ATU_UPPER_BASE);
#endif
	axxia_pcie_writel_rc(hose, data->cfg1_base + data->cfg1_size - 1,
			     PCIE_ATU_LIMIT);
	axxia_pcie_writel_rc(hose, busdev, PCIE_ATU_LOWER_TARGET);
	axxia_pcie_writel_rc(hose, 0, PCIE_ATU_UPPER_TARGET);
	axxia_pcie_writel_rc(hose, PCIE_ATU_ENABLE, PCIE_ATU_CR2);
}

static void axxia_pcie_prog_viewport_mem_outbound(struct pci_controller *hose)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	/* Program viewport 0 : OUTBOUND : MEM */
	axxia_pcie_writel_rc(hose,
			     PCIE_ATU_REGION_OUTBOUND | PCIE_ATU_REGION_INDEX2,
			     PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_MEM, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, data->mem_mod_base, PCIE_ATU_LOWER_BASE);
#if defined(CONFIG_AXXIA_ANY_XLF)
	axxia_pcie_writel_rc(hose, (data->mem_mod_base >> 32),
			     PCIE_ATU_UPPER_BASE);
#endif
	axxia_pcie_writel_rc(hose, data->mem_mod_base + data->mem_size - 1,
			     PCIE_ATU_LIMIT);
	axxia_pcie_writel_rc(hose, data->mem_bus_addr, PCIE_ATU_LOWER_TARGET);
	axxia_pcie_writel_rc(hose, upper_32_bits(data->mem_bus_addr),
			     PCIE_ATU_UPPER_TARGET);
	axxia_pcie_writel_rc(hose, PCIE_ATU_ENABLE, PCIE_ATU_CR2);
}

static void axxia_pcie_prog_viewport_io_outbound(struct pci_controller *hose)
{
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	/* Program viewport 1 : OUTBOUND : IO */
	axxia_pcie_writel_rc(hose,
			     PCIE_ATU_REGION_OUTBOUND | PCIE_ATU_REGION_INDEX3,
			     PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_IO, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, data->io_mod_base, PCIE_ATU_LOWER_BASE);
	axxia_pcie_writel_rc(hose, data->io_mod_base + data->io_size - 1,
			     PCIE_ATU_LIMIT);
	axxia_pcie_writel_rc(hose, data->io_bus_addr, PCIE_ATU_LOWER_TARGET);
	axxia_pcie_writel_rc(hose, upper_32_bits(data->io_bus_addr),
			     PCIE_ATU_UPPER_TARGET);
	axxia_pcie_writel_rc(hose, PCIE_ATU_ENABLE, PCIE_ATU_CR2);
}


static int axxia_pcie_rd_other_conf(struct pci_controller *hose,
	u32 devfn, int where, int size, u32 *val)
{
	u32 address, busdev;
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	int ret = 0;

	busdev = PCIE_ATU_BUS(PCI_BUS(devfn)) | PCIE_ATU_DEV(PCI_DEV(devfn))
		| PCIE_ATU_FUNC(PCI_FUNC(devfn));
	address = where & ~0x3;

	/* Primary bus */
	if (PCI_BUS(devfn) == 1) {
		axxia_pcie_prog_viewport_cfg0(hose, busdev);
		ret = axxia_pcie_cfg_read((void __iomem *)data->cfg0_base
			+ address, where, size, val);
		axxia_pcie_prog_viewport_mem_outbound(hose);
	} else {
		axxia_pcie_prog_viewport_cfg1(hose, busdev);
		ret = axxia_pcie_cfg_read((void __iomem *)data->cfg1_base
			+ address, where, size, val);
		axxia_pcie_prog_viewport_io_outbound(hose);
	}
	return ret;
}

static int axxia_pcie_wr_other_conf(struct pci_controller *hose,
	u32 devfn, int where, int size, u32 val)
{
	u32 address, busdev;
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;
	int ret;

	busdev = PCIE_ATU_BUS(PCI_BUS(devfn)) | PCIE_ATU_DEV(PCI_DEV(devfn))
		| PCIE_ATU_FUNC(PCI_FUNC(devfn));
	address = where & ~0x3;

	/* Primary bus */
	if (PCI_BUS(devfn) == 1) {
		axxia_pcie_prog_viewport_cfg0(hose, busdev);
		ret = axxia_pcie_cfg_write((void __iomem *)data->cfg0_base
			+ address, where, size, val);
		axxia_pcie_prog_viewport_mem_outbound(hose);
	} else {
		axxia_pcie_prog_viewport_cfg1(hose, busdev);
		ret = axxia_pcie_cfg_write((void __iomem *)data->cfg1_base
			+ address, where, size, val);
		axxia_pcie_prog_viewport_io_outbound(hose);
	}
	return ret;
}

static int axxia_pcie_rd_own_conf(struct pci_controller *hose, int where,
	int size, u32 *val)
{
	int ret;
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	ret = axxia_pcie_cfg_read((void __iomem *)data->dbi_base
		+ (where & ~0x3), where, size, val);
	return ret;
}

static int axxia_pcie_wr_own_conf(struct pci_controller *hose, int where,
	int size, u32 val)
{
	int ret;
	struct pci_hose_data *data;
	data = (struct pci_hose_data *)hose->priv_data;

	ret = axxia_pcie_cfg_write((void __iomem *)data->dbi_base
		+ (where & ~0x3), where, size, val);
	return ret;
}

/* Read the configuration space */
static int pcie_read_config(struct pci_controller *hose, unsigned int devfn,
	int offset, int len, u32 *val) {
	*val = 0;
	int ret;

	/*
	 * Only single device/single function is supported for the primary and
	 * secondary buses
	 */
	if (((!((PCI_FUNC(devfn) == 0) && (PCI_DEV(devfn) == 0))) &&
	     (PCI_BUS(devfn) == 0)) ||
	    (!(PCI_DEV(devfn) == 0) && (PCI_BUS(devfn) == 1))) {
		return 0;
	}

	if (PCI_BUS(devfn) == 0)
		ret = axxia_pcie_rd_own_conf(hose, offset, len, val);
	else
		ret = axxia_pcie_rd_other_conf(hose, devfn, offset, len, val);

	return ret;
}

/* Write the configuration space */
static int pcie_write_config(struct pci_controller *hose, unsigned int devfn,
	int offset, int len, u32 val) {
	int ret;

	/*
	 * Same constraints as in pcie_read_config().
	 */
	if (PCI_BUS(devfn) >= 16)
		return 0;

	if (((!((PCI_FUNC(devfn) == 0) && (PCI_DEV(devfn) == 0))) &&
	     (PCI_BUS(devfn) == 0)) ||
	    (!(PCI_DEV(devfn) == 0) && (PCI_BUS(devfn) == 1))) {
		return 0;
	}

	/*
	 * addressing is different for local config access vs.
	 * access through the mapped config space. We need to
	 * translate the offset for mapped config access
	 */
	if (PCI_BUS(devfn) == 0)
		ret = axxia_pcie_wr_own_conf(hose, offset, len, val);
	else
		ret = axxia_pcie_wr_other_conf(hose, devfn, offset, len, val);

	return ret;
}

int pcie_read_config_byte(struct pci_controller *hose, pci_dev_t dev,
	int offset, u8 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 1, &v);
	*val = (u8)v;
	return rv;
}

int pcie_read_config_word(struct pci_controller *hose, pci_dev_t dev,
	int offset, u16 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 2, &v);
	*val = (u16)v;
	return rv;
}

int pcie_read_config_dword(struct pci_controller *hose, pci_dev_t dev,
	int offset, u32 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 4, &v);
	*val = (u32)v;
	return rv;
}

int pcie_write_config_byte(struct pci_controller *hose, pci_dev_t dev,
	int offset, u8 val)
{
	return pcie_write_config(hose, (u32)dev, offset, 1, val);
}

int pcie_write_config_word(struct pci_controller *hose, pci_dev_t dev,
	int offset, u16 val)
{
	return pcie_write_config(hose, (u32)dev, offset, 2, (u32)val);
}

int pcie_write_config_dword(struct pci_controller *hose, pci_dev_t dev,
	int offset, u32 val)
{
	return pcie_write_config(hose, (u32)dev, offset, 4, (u32)val);
}

#ifdef ENABLE_LOS_WA
static int
axxia_pcie_los_wa(struct pci_controller *hose)
{
	unsigned int value;
	unsigned int max_loops = 10000; /* determined experimentally */

	/*
	  There are four SerDes, each with 2 lanes or channels.  The
	  following uses one byte for each SerDes, and in each byte,
	  one nibble for each lane.  Only lanes that are in RC mode
	  and configured for PCIe should be part of the work around.
	*/

	unsigned int lane_mask;

	/* Which PEI is being used... */
	int pei;

#if defined(CONFIG_AXXIA_ANY_56XX)
	struct pci_hose_data *priv;

	priv = (struct pci_hose_data *)hose->priv_data;
#endif

#ifdef CONFIG_AXXIA_ANY_XLF

	pei = 0;

#else  /* CONFIG_AXXIA_ANY_XLF */

	if (PCIE0_DBI_BASE == priv->dbi_base) {
		pei = 0;
#ifdef ACP_PEI1
	} else if (PCIE1_DBI_BASE == priv->dbi_base) {
		pei = 1;
#endif
#ifdef ACP_PEI2
	} else if (PCIE2_DBI_BASE == priv->dbi_base) {
		pei = 2;
#endif
	} else {
		error("Invalid Argument!");

		return -1;
	}

#endif	/* CONFIG_AXXIA_ANY_XLF */

	/* If PEI0, make sure it is configured as the root complex. */
	if ((0 == pei) && (0 == (pciesrio->control & 0x80)))
		return 0;

	/*
	  The "control" value in the parameters defines the number of
	  lanes used.  Use bits 25:22 to initialize "lane_mask".
	*/

#ifdef CONFIG_AXXIA_ANY_XLF

	switch ((pciesrio->control & 0x3c00000) >> 22) {
	case 1:
		lane_mask = 0x00000011;
		break;
	case 2:
		lane_mask = 0x00000001;
		break;
	default:
		return 0;
		break;
	}

#else  /* CONFIG_AXXIA_ANY_XLF */

	switch ((pciesrio->control & 0x3c00000) >> 22) {
	case 1:
		/* PEI0x4 and PEI1x4 */
		if (0 == pei)
			lane_mask = 0x00001111;
		else if (1 == pei)
			lane_mask = 0x11110000;
		else
			return 0;

		break;
	case 2:
		/* PEI0x2, PEI2x2, and PEI1x2 */
		if (0 == pei)
			lane_mask = 0x00000011;
		else if (1 == pei)
			lane_mask = 0x00110000;
		else if (2 == pei)
			lane_mask = 0x00001100;
		else
			return 0;

		break;
	case 3:
		/* PEI0x2 and PEI2x2 */
		if (0 == pei)
			lane_mask = 0x00000011;
		else if (2 == pei)
			lane_mask = 0x11000000;
		else
			return 0;

		break;
	case 4:
		/* PEI2x2 */
		if (2 == pei)
			lane_mask = 0x11000000;
		else
			return 0;

		break;
	default:
		return 0;
		break;
	}

#endif	/* CONFIG_AXXIA_ANY_XLF */

	/* Run the LOS work around until a link is established. */

#if defined(CONFIG_AXXIA_ANY_56XX)

	/*
	  On 5600, the offsets are

	  LANE0_DIG_ASIC_RX_ASIC_IN_0 0x2022
	  LANE0_DIG_ASIC_RX_ASIC_OUT_0 0x202e
	  LANE0_IDG_ASIC_RX_OVRD_IN_0 0x200a
	*/

#define MAX_TARGET 4
#define LANE0_DIG_ASIC_RX_ASIC_IN_0  0x2022
#define LANE0_DIG_ASIC_RX_ASIC_OUT_0 0x202e
#define LANE0_IDG_ASIC_RX_OVRD_IN_0  0x200a
#define LANE1_DIG_ASIC_RX_ASIC_IN_0  0x2222
#define LANE1_DIG_ASIC_RX_ASIC_OUT_0 0x222e
#define LANE1_IDG_ASIC_RX_OVRD_IN_0  0x220a

#elif defined(CONFIG_AXXIA_ANY_XLF)

	/*
	    On XLF, the offsets are

	  LANE0_DIG_ASIC_RX_ASIC_IN_0 0x4044
	  LANE0_DIG_ASIC_RX_ASIC_OUT_0 0x405c
	  LANE0_IDG_ASIC_RX_OVRD_IN_0 0x4014
	*/

#define MAX_TARGET 1
#define LANE0_DIG_ASIC_RX_ASIC_IN_0  0x4044
#define LANE0_DIG_ASIC_RX_ASIC_OUT_0 0x405c
#define LANE0_IDG_ASIC_RX_OVRD_IN_0  0x4014
#define LANE1_DIG_ASIC_RX_ASIC_IN_0  0x4444
#define LANE1_DIG_ASIC_RX_ASIC_OUT_0 0x445c
#define LANE1_IDG_ASIC_RX_OVRD_IN_0  0x4414

#else
#error "Invalid Architecture"
#endif

	while (0 < --max_loops) {
		int i;
		unsigned short temp;

		/* 
		   In all cases (see the initialization of lane_mask
		   above), either both lanes or none are used in each
		   HSS.
		 */

		for (i = 1; i <= MAX_TARGET; ++i) {
			if (0 == (lane_mask & (0xff << ((i - 1) * 8))))
				continue;

			ncr_read(NCP_REGION_ID(0x115, i), 0,
				 LANE0_DIG_ASIC_RX_ASIC_IN_0, 2, &temp);

			if (2 == ((temp & 0x180) >> 7)) {
				ncr_read(NCP_REGION_ID(0x115, i), 0,
					 LANE0_DIG_ASIC_RX_ASIC_OUT_0,
					 2, &temp);

				if (0 != (temp & 2))
					temp = 0x4700;
				else
					temp = 0x0700;

				ncr_write(NCP_REGION_ID(0x115, i), 0,
					  LANE0_IDG_ASIC_RX_OVRD_IN_0,
					  2, &temp);
			}

			ncr_read(NCP_REGION_ID(0x115, i), 0,
				 LANE1_DIG_ASIC_RX_ASIC_IN_0, 2, &temp);

			if (2 == ((temp & 0x180) >> 7)) {
				ncr_read(NCP_REGION_ID(0x115, i), 0,
					 LANE1_DIG_ASIC_RX_ASIC_OUT_0,
					 2, &temp);

				if (0 != (temp & 2))
					temp = 0x4700;
				else
					temp = 0x0700;

				ncr_write(NCP_REGION_ID(0x115, i), 0,
					  LANE1_IDG_ASIC_RX_OVRD_IN_0,
					  2, &temp);
			}
		}

		axxia_cc_gpreg_readl(hose, PEI_SII_PWR_MGMT_REG, &value);

		if (0 != (value & (1 << 12)) && 0x11 == ((value & 0x3f0) >> 4))
			break;
	}

	if (0 == max_loops)
		return -1;

	return 0;
}
#endif	/* ENABLE_LOS_WA */

int axxia_pcie_link_up(struct pci_controller *hose)
{
	u32 rdlh_lnk, smlh_lnk, smlh_state;

	debug("In axxia_pcie_link_up \n\r");

	axxia_cc_gpreg_readl(hose, PEI_SII_PWR_MGMT_REG, &smlh_lnk);
	axxia_cc_gpreg_readl(hose, PEI_SII_DBG_0_MON_REG, &rdlh_lnk);

	axxia_cc_gpreg_readl(hose, PEI_SII_PWR_MGMT_REG, &smlh_state);
	smlh_state = (smlh_state & PEI_SMLH_LINK_STATE) >> 4;
	if ( (smlh_state != 0x11) && (smlh_state != 0x23) ) {
		debug("smlh_state = 0x%x\n", smlh_state);
		debug("PCIe LINK IS NOT UP\n");
		return 0;
	}

	debug("smlh_state = 0x%x\n", smlh_state);

	return 1;
}

void axxia_pcie_setup_rc(struct pci_controller *hose)
{
	u32 val;
	u32 membase;
	u32 memlimit;
	struct pci_hose_data *data;

	debug("In axxia_pcie_setup_rc \n\r");

	data = (struct pci_hose_data *)hose->priv_data;

	/* setup bus numbers */
	axxia_pcie_readl_rc(hose, PCI_PRIMARY_BUS, &val);

	val &= 0xff000000;
	val |= 0x00010100;
	axxia_pcie_writel_rc(hose, val, PCI_PRIMARY_BUS);

	/* Setup memory base and limit. */
	membase = ((u32)data->mem_mod_base & 0xfff00000) >> 16;
	memlimit = (data->mem_size + (u32)data->mem_mod_base) & 0xfff00000;
	val = memlimit | membase;
	axxia_pcie_writel_rc(hose, val, PCI_MEMORY_BASE);
	
	/* setup command register */
	axxia_pcie_readl_rc(hose, PCI_COMMAND, &val);
	
	val &= 0xffff0000;
	val |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
		PCI_COMMAND_MASTER | PCI_COMMAND_SERR;
	axxia_pcie_writel_rc(hose, val, PCI_COMMAND);

	/* GEN2_CTRL_OFF */
	axxia_pcie_readl_rc(hose, PCIE_LINK_WIDTH_SPEED_CONTROL, &val);
	val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
	switch (data->lanes) {
	case 2:
		val |= PORT_LOGIC_LINK_WIDTH_2_LANES;
		break;
	case 4:
		val |= PORT_LOGIC_LINK_WIDTH_4_LANES;
		break;
	case 8:
		val |= PORT_LOGIC_LINK_WIDTH_8_LANES;
		break;
	case 1:
	default:
		val |= PORT_LOGIC_LINK_WIDTH_1_LANES;
	}
	axxia_pcie_writel_rc(hose, val, PCIE_LINK_WIDTH_SPEED_CONTROL);

	/* PORT_LINK_CTRL_OFF */
	axxia_pcie_readl_rc(hose, PCIE_PORT_LINK_CONTROL, &val);
	val &= ~PORT_LINK_MODE_MASK;
	switch (data->lanes) {
	case 2:
		val |= PORT_LINK_MODE_2_LANES;
		break;
	case 4:
		val |= PORT_LINK_MODE_4_LANES;
		break;
	case 8:
		val |= PORT_LINK_MODE_8_LANES;
		break;
	case 1:
	default:
		val |= PORT_LINK_MODE_1_LANES;
	}
	axxia_pcie_writel_rc(hose, val, PCIE_PORT_LINK_CONTROL);
	
#ifdef ENABLE_LOS_WA
	/* The default value of GEN3_EQ_CONTROL is not correct. */
	axxia_pcie_writel_rc(hose, 0x1017221, 0x8a8);

	/* LTSSM enable */
	axxia_cc_gpreg_readl(hose, PEI_GENERAL_CORE_CTL_REG, &val);
	val |= 0x1;
	axxia_cc_gpreg_writel(hose, 0x1, PEI_GENERAL_CORE_CTL_REG);

	if (0 != axxia_pcie_los_wa(hose))
		error("The LOS Work Around Failed!");
#else  /* ENABLE_LOS_WA */
	/* The default value of GEN3_EQ_CONTROL is not correct. */
	axxia_pcie_writel_rc(hose, 0x1017201, 0x8a8);

	/* LTSSM enable */
	axxia_cc_gpreg_readl(hose, PEI_GENERAL_CORE_CTL_REG, &val);
	mdelay(100);
	val |= 0x1;
	axxia_cc_gpreg_writel(hose, 0x1, PEI_GENERAL_CORE_CTL_REG);
	mdelay(100);
#endif	/* ENABLE_LOS_WA */

	return;
}

static int axxia_pcie_establish_link(struct pci_controller *hose)
{
	/* setup root complex */
	axxia_pcie_setup_rc(hose);

	if (!axxia_pcie_link_up(hose))
		return 1;

	debug("Link up\n");

	return 0;
}

/* program correct class for RC */
static void pci_axxia_program_rc_class(struct pci_controller *hose)
{
	u32 dbi_ro_wr_en;
	/* program correct class for RC */
	axxia_pcie_readl_rc(hose, 0x8bc, &dbi_ro_wr_en);
	/* DBI_RO_WR_EN */
	if (!(dbi_ro_wr_en & 0x1))
		axxia_pcie_writel_rc(hose, (dbi_ro_wr_en | 0x1), 0x8bc);
	axxia_pcie_wr_own_conf(hose, PCI_CLASS_DEVICE, 2, PCI_CLASS_BRIDGE_PCI);
	/* DBI_RO_WR_EN */
	if (!(dbi_ro_wr_en & 0x1))
		axxia_pcie_writel_rc(hose, dbi_ro_wr_en, 0x8bc);
}

int pci_axxia_init(struct pci_controller *hose, int port, int lanes)
{
	pci_set_ops(hose,
		    pcie_read_config_byte,
		    pcie_read_config_word,
		    pcie_read_config_dword,
		    pcie_write_config_byte,
		    pcie_write_config_word,
		    pcie_write_config_dword);

	switch (port) {
#ifdef ACP_PEI0
	case 0:
		debug("PEI0 Root Complex.\n");
		/* PEI0 RC mode */
		hose_data[port].dbi_base = PCIE0_DBI_BASE;
		hose_data[port].axi_gpreg_base = PCIE0_AXI_GPREG_BASE;
		hose_data[port].cc_gpreg_base = PCIE0_CC_GPREG_BASE;
		hose_data[port].cfg0_base = CONFIG_SYS_PCIE0_CFG0BASE;
		hose_data[port].cfg1_base = CONFIG_SYS_PCIE0_CFG1BASE;
		hose_data[port].cfg0_size = CONFIG_SYS_PCIE0_CFG0SIZE;
		hose_data[port].cfg1_size = CONFIG_SYS_PCIE0_CFG1SIZE;
		hose_data[port].mem_mod_base = CONFIG_SYS_PCIE0_MEMBASE;
		hose_data[port].mem_size = CONFIG_SYS_PCIE0_MEMSIZE;
		hose_data[port].mem_bus_addr = CONFIG_PCIE0_BUS_START;
		/* Hard code lanes to 4 for now */
		hose_data[port].lanes = lanes;
		break;
#endif
#ifdef ACP_PEI1
	case 1:
		debug("PEI1 Root Complex.\n");
		/* PEI1 RC mode */
		hose_data[port].dbi_base = PCIE1_DBI_BASE;
		hose_data[port].axi_gpreg_base = PCIE1_AXI_GPREG_BASE;
		hose_data[port].cc_gpreg_base = PCIE1_CC_GPREG_BASE;
		hose_data[port].cfg0_base = CONFIG_SYS_PCIE1_CFG0BASE;
		hose_data[port].cfg1_base = CONFIG_SYS_PCIE1_CFG1BASE;
		hose_data[port].cfg0_size = CONFIG_SYS_PCIE1_CFG0SIZE;
		hose_data[port].cfg1_size = CONFIG_SYS_PCIE1_CFG1SIZE;
		hose_data[port].mem_mod_base = CONFIG_SYS_PCIE1_MEMBASE;
		hose_data[port].mem_size = CONFIG_SYS_PCIE1_MEMSIZE;
		hose_data[port].mem_bus_addr = CONFIG_PCIE1_BUS_START;
		hose_data[port].lanes = lanes;
		break;
#endif
#ifdef ACP_PEI2
	case 2:
		debug("PEI2 Root Complex.\n");
		/* PEI2 RC mode */
		hose_data[port].dbi_base = PCIE2_DBI_BASE;
		hose_data[port].axi_gpreg_base = PCIE2_AXI_GPREG_BASE;
		hose_data[port].cc_gpreg_base = PCIE2_CC_GPREG_BASE;
		hose_data[port].cfg0_base = CONFIG_SYS_PCIE2_CFG0BASE;
		hose_data[port].cfg1_base = CONFIG_SYS_PCIE2_CFG1BASE;
		hose_data[port].cfg0_size = CONFIG_SYS_PCIE2_CFG0SIZE;
		hose_data[port].cfg1_size = CONFIG_SYS_PCIE2_CFG1SIZE;
		hose_data[port].mem_mod_base = CONFIG_SYS_PCIE2_MEMBASE;
		hose_data[port].mem_size = CONFIG_SYS_PCIE2_MEMSIZE;
		hose_data[port].mem_bus_addr = CONFIG_PCIE2_BUS_START;
		hose_data[port].lanes = lanes;
		break;
#endif
	}
	hose->priv_data = (void *)&hose_data[port];

	/* PCI memory space */
	pci_set_region(hose->regions + 0,
		       hose_data[port].mem_mod_base,
		       hose_data[port].mem_mod_base,
		       hose_data[port].mem_size,
		       PCI_REGION_MEM);
	hose->region_count++;
	pci_register_hose(hose);

	debug("Jumping to axxia_pcie_establish_link \n\r"); //jl

	if (axxia_pcie_establish_link(hose)) {
		debug("Failed to establish PCIe link\n");
		return 1;
	}

	pci_axxia_program_rc_class(hose);

	hose->first_busno = 0;
	hose->current_busno = hose->last_busno+1;
	hose->last_busno = 0xff;
	hose->last_busno = pci_hose_scan(hose);

	return hose->last_busno;
}

void
pci_init_board(void)
{
#if defined(CONFIG_TARGET_SIMULATION)
	debug("PCIe Skipped for Simulation");

	return;
#endif

#if defined(ACP_PEI0) || defined(ACP_PEI1) || defined(ACP_PEI2)
	unsigned int pei0_lanes = 0;
	unsigned int global0_cfg;
#if defined(CONFIG_AXXIA_ANY_56XX)
	unsigned int global1_cfg;
	unsigned int sw_port_config0;
	unsigned int sw_port_config1;
#endif
#if defined(ACP_PEI1)
	unsigned int pei1_lanes = 0;
#endif
#if defined(ACP_PEI2)
	unsigned int pei2_lanes = 0;
#endif

	ncr_read32(NCP_REGION_ID(0x115, 0x0), 0x0, &global0_cfg);
	debug("0x115.0x0.0x0=0x%x\n", global0_cfg);
#if defined(CONFIG_AXXIA_ANY_56XX)
	ncr_read32(NCP_REGION_ID(0x115, 0x0), 0x4, &global1_cfg);
	debug("0x115.0x0.0x4=0x%x\n", global1_cfg);
	sw_port_config0 = (global0_cfg & 0x1c000000) >> 26;
	sw_port_config1 = (global1_cfg & 0x00c00000) >> 22;
#endif

#if defined(CONFIG_AXXIA_ANY_XLF)
	if (2 == ((pciesrio->control & 0x3c00000 )>> 22))
		pei0_lanes = 1;
	else
		pei0_lanes = 2;

	debug("pei0_lanes = %d\n", pei0_lanes);
#else  /* CONFIG_AXXIA_ANY_XLF */
	switch (sw_port_config0) {
	case 0:
	case 2:
		if (sw_port_config1 == 0)
			pei0_lanes = 8;
		break;
	case 1:
		pei0_lanes = 4;
		break;
	case 3:
		pei0_lanes = 2;
#if defined(ACP_PEI2)
		pei2_lanes = 2;
#endif
		break;
	case 7:
		pei0_lanes = 2;
		break;
	}

#if defined(ACP_PEI1) || defined(ACP_PEI2)
	switch (sw_port_config1) {
	case 1:
		pei1_lanes = 4;
		break;
	case 2:
		pei1_lanes = 2;
		break;
	case 3:
		pei1_lanes = 2;
#if defined(ACP_PEI2)
		pei2_lanes = 2;
#endif
		break;
	}
#endif	/* ACP_PEI1 || ACP_PEI2 */

	debug("pei0_lanes = %d\n", pei0_lanes);

#if defined(ACP_PEI1)
	debug("pei1_lanes = %d\n", pei1_lanes);
#endif

#if defined(ACP_PEI2)
	debug("pei2_lanes = %d\n", pei2_lanes);
#endif

#endif	/* CONFIG_AXXIA_ANY_XLF */
#endif	/* ACP_PEI0 || ACP_PEI1 || ACP_PEI2 */

#ifdef ACP_PEI0
	/* If PEI0 is enabled and in RC mode, enumerate it. */
	if (0 != (global0_cfg & (1 << 0)) &&  0 != (global0_cfg & (1 << 22))) {
		debug("enumerating hose[0]\n");
		(void)pci_axxia_init(&hose[0], 0, pei0_lanes);
	}
#endif

#ifdef ACP_PEI1
	/* If PEI1 is enabled, enumerate it. */
	if (0 != (global0_cfg & (1 << 1))) {
		debug("enumerating hose[1]\n");
		(void)pci_axxia_init(&hose[1], 1, pei1_lanes);
	}
#endif

#ifdef ACP_PEI2
	/* If PEI2 is enabled, enumerate it. */
	if (0 != (global0_cfg & (1 << 2))) {
		debug("enumerating hose[2]\n");
		(void)pci_axxia_init(&hose[2], 2, pei2_lanes);
	}
#endif

	return;
}

#endif /* CONFIG_PCI */
