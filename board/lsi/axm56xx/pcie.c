#include <common.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <asm/types.h>
#include <pci.h>
#include <config.h>

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

#define PCIE_LINK_WIDTH_SPEED_CONTROL   0x80C
#define PORT_LOGIC_SPEED_CHANGE         (0x1 << 17)
#define PORT_LOGIC_LINK_WIDTH_MASK      (0x1ff << 8)
#define PORT_LOGIC_LINK_WIDTH_1_LANES   (0x1 << 8)
#define PORT_LOGIC_LINK_WIDTH_2_LANES   (0x2 << 8)
#define PORT_LOGIC_LINK_WIDTH_4_LANES   (0x4 << 8)

#define PCIE_MSI_ADDR_LO                0x820
#define PCIE_MSI_ADDR_HI                0x824
#define PCIE_MSI_INTR0_ENABLE           0x828
#define PCIE_MSI_INTR0_MASK             0x82C
#define PCIE_MSI_INTR0_STATUS           0x830

#define PCIE_ATU_VIEWPORT               0x900
#define PCIE_ATU_REGION_INBOUND         (0x1 << 31)
#define PCIE_ATU_REGION_OUTBOUND        (0x0 << 31)
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
	axxia_pcie_writel_rc(hose, (data->cfg0_base >> 32),
			     PCIE_ATU_UPPER_BASE);
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
	axxia_pcie_writel_rc(hose, (data->cfg1_base >> 32),
			     PCIE_ATU_UPPER_BASE);
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
			     PCIE_ATU_REGION_OUTBOUND | PCIE_ATU_REGION_INDEX0,
			     PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_MEM, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, data->mem_mod_base, PCIE_ATU_LOWER_BASE);
	axxia_pcie_writel_rc(hose, (data->mem_mod_base >> 32),
			     PCIE_ATU_UPPER_BASE);
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
			     PCIE_ATU_REGION_OUTBOUND | PCIE_ATU_REGION_INDEX1,
			     PCIE_ATU_VIEWPORT);
	axxia_pcie_writel_rc(hose, PCIE_ATU_TYPE_IO, PCIE_ATU_CR1);
	axxia_pcie_writel_rc(hose, data->io_mod_base, PCIE_ATU_LOWER_BASE);
	axxia_pcie_writel_rc(hose, (data->io_mod_base >> 32),
			     PCIE_ATU_UPPER_BASE);
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

int axxia_pcie_link_up(struct pci_controller *hose)
{
	u32 rdlh_lnk, smlh_lnk, smlh_state;

	axxia_cc_gpreg_readl(hose, PEI_SII_PWR_MGMT_REG, &smlh_lnk);
	axxia_cc_gpreg_readl(hose, PEI_SII_DBG_0_MON_REG, &rdlh_lnk);

	axxia_cc_gpreg_readl(hose, PEI_SII_PWR_MGMT_REG, &smlh_state);
	smlh_state = (smlh_state & PEI_SMLH_LINK_STATE) >> 4;
	if (smlh_state != 0xb) {
		printf("smlh_state = 0x%x\n", smlh_state);
		printf("PCIe LINK IS NOT UP\n");
		return 0;
	}
	return 1;
}

void axxia_pcie_setup_rc(struct pci_controller *hose)
{
	u32 val;
	u32 membase;
	u32 memlimit;
	struct pci_hose_data *data;

	data = (struct pci_hose_data *)hose->priv_data;

	/* set the number of lanes */
	axxia_pcie_readl_rc(hose, PCIE_PORT_LINK_CONTROL, &val);
	val &= ~PORT_LINK_MODE_MASK;
	switch (data->lanes) {
	case 1:
		val |= PORT_LINK_MODE_1_LANES;
	break;
	case 2:
		val |= PORT_LINK_MODE_2_LANES;
	break;
	case 4:
		val |= PORT_LINK_MODE_4_LANES;
	break;
	}
	axxia_pcie_writel_rc(hose, val, PCIE_PORT_LINK_CONTROL);

	/* set link width speed control register */
	axxia_pcie_readl_rc(hose, PCIE_LINK_WIDTH_SPEED_CONTROL, &val);
	val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
	switch (data->lanes) {
	case 1:
		val |= PORT_LOGIC_LINK_WIDTH_1_LANES;
	break;
	case 2:
		val |= PORT_LOGIC_LINK_WIDTH_2_LANES;
	break;
	case 4:
		val |= PORT_LOGIC_LINK_WIDTH_4_LANES;
	break;
	}

	axxia_pcie_writel_rc(hose, val, PCIE_LINK_WIDTH_SPEED_CONTROL);

	/* setup bus numbers */
	axxia_pcie_readl_rc(hose, PCI_PRIMARY_BUS, &val);
	val &= 0xff000000;
	val |= 0x00010100;
	axxia_pcie_writel_rc(hose, val, PCI_PRIMARY_BUS);
	/* setup memory base, memory limit */
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

	/* LTSSM enable */
	axxia_cc_gpreg_readl(hose, PEI_GENERAL_CORE_CTL_REG, &val);
	val |= 0x1;
	axxia_cc_gpreg_writel(hose, 0x1, PEI_GENERAL_CORE_CTL_REG);
}

static int axxia_pcie_establish_link(struct pci_controller *hose)
{

	if (axxia_pcie_link_up(hose)) {
		printf("Link already up\n");
		return 0;
	}

	/* setup root complex */
	axxia_pcie_setup_rc(hose);

	if (axxia_pcie_link_up(hose))
		printf("Link up\n");

	return 0;
}

int pci_axxia_init(struct pci_controller *hose, int port)
{
	u32 val;

	pci_set_ops(hose,
		    pcie_read_config_byte,
		    pcie_read_config_word,
		    pcie_read_config_dword,
		    pcie_write_config_byte,
		    pcie_write_config_word,
		    pcie_write_config_dword);

	switch (port) {
	case 0:
		printf("PEI0 Root Complex.\n");
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
		break;
	case 1:
		printf("PEI1 Root Complex.\n");
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
		break;
	case 2:
		printf("PEI2 Root Complex.\n");
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
		break;
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

	axxia_pcie_establish_link(hose);
	/* program correct class for RC */
	axxia_pcie_wr_own_conf(hose, PCI_CLASS_DEVICE, 2, PCI_CLASS_BRIDGE_PCI);

	axxia_pcie_rd_own_conf(hose, PCIE_LINK_WIDTH_SPEED_CONTROL, 4, &val);
	val |= PORT_LOGIC_SPEED_CHANGE;
	axxia_pcie_wr_own_conf(hose, PCIE_LINK_WIDTH_SPEED_CONTROL, 4, val);

	hose->first_busno = 0;
	hose->current_busno = hose->last_busno+1;
	hose->last_busno = 0xff;
	hose->last_busno = pci_hose_scan(hose);

	return hose->last_busno;

}

void
pci_init_board(void)
{
	/* PEI0 is enabled, enumerate it */
	(void)pci_axxia_init(&hose[0], 0);
	/* PEI1 is enabled, enumerate it */
	(void)pci_axxia_init(&hose[1], 1);
	/* PEI2 is enabled, enumerate it */
	(void)pci_axxia_init(&hose[2], 2);
}

#endif /* CONFIG_PCI */
