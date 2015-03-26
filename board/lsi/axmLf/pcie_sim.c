#include <common.h>
#include <command.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <pci.h>
#include <config.h>

#undef DEBUG_PCIE

#ifdef CONFIG_PCI

#define ACPX1_PCIE_MPAGE_UPPER(n) (0x1010 + (n * 8))
#define ACPX1_PCIE_MPAGE_LOWER(n) (0x1014 + (n * 8))

#define U64_TO_U32_LOW(val)     ((u32)((val) & 0x00000000ffffffffULL))
#define U64_TO_U32_HIGH(val)    ((u32)((val) >> 32))

static struct pci_controller hose[CONFIG_SYS_PCIE_NR_PORTS];

/* get the base address of the configuration space */
static u8 *pcie_get_base(struct pci_controller *hose, unsigned int devfn)
{
	u8 *base = (u8 *)hose->cfg_data;
	int dev, fn;
	int cfg_type = 0;
	u64 addr;
	unsigned mpage;

	if (PCI_BUS(devfn) == 0) {
		return (u8 *)hose->cfg_addr;
	} else {
		dev = PCI_DEV(devfn);
		fn = PCI_FUNC(devfn);

		if (dev > 31)
			return NULL;

		/* Primary bus */
		if (PCI_BUS(devfn) == 1)
			cfg_type = 0;
		else
			cfg_type = 1;
#ifdef DEBUG_PCIE
		printf("pcie_get_base: bus = %d -- cfg type = %d\n",
		       PCI_BUS(devfn), cfg_type);
#endif

		/* build the mpage register */
		mpage = (PCI_BUS(devfn) << 11) |
		(dev << 6) |
		(cfg_type << 5);

		mpage |= 0x10;	/* enable MPAGE for configuration access */
		mpage |= (fn << 19);

		addr = ((u64)hose->cfg_addr) + ACPX1_PCIE_MPAGE_UPPER(7);
		writel(0x0, addr);
		addr = ((u64)hose->cfg_addr) + ACPX1_PCIE_MPAGE_LOWER(7);
#ifdef DEBUG_PCIE
		printf("pcie_get_base: %02x:%02x:%02x setting mpage = 0x%08x in addr = 0x%08x\n",
		       PCI_BUS(devfn), dev, fn, mpage, addr);
#endif
		writel(mpage, addr);
	}

	return base;
}

/* Read the configuration space */
static int pcie_read_config(struct pci_controller *hose, unsigned int devfn,
	int offset, int len, u32 *val) {
	u8 *address;
	*val = 0;
	u64 bus_addr;
	u32 val32;
	int bo = offset & 0x3;
	int wo;

	/*
	 * Only single device/single function is supported for the primary and
	 * secondary buses
	 */
	if (((!((PCI_FUNC(devfn) == 0) && (PCI_DEV(devfn) == 0))) &&
	     (PCI_BUS(devfn) == 0)) ||
	    (!(PCI_DEV(devfn) == 0) && (PCI_BUS(devfn) == 1))) {
		return 0;
	}

	address = pcie_get_base(hose, devfn);
	if (address == NULL)
		return 0;
#ifdef DEBUG_PCIE
	printf("pcie_read_config:  cfg space base_address  = 0x%x, cfg_data = 0x%x\n",
	       address, hose->cfg_data);
#endif

	if (PCI_BUS(devfn) == 0) {
		wo = offset & 0xfffffffc;
		bus_addr = (u64)address+wo;
	} else {
		/*
		 * mapped config space only supports 32-bit access
		 * AXI address [3:0] is not used at all.
		 * AXI address[9:4] becomes register number.
		 * AXI address[13:10] becomes Ext. register number
		 * AXI address[17:14] becomes 1st DWBE for configuration
		 * read only.
		 * AXI address[29:27] is used to select one of 8 Mpage
		 * registers.
		 */
		bus_addr = (u64)address + (offset << 2);

		switch (len) {
		case 1:
			bus_addr |=  ((1 << bo)) << 14;
			break;
		case 2:
			bus_addr |=  ((3 << bo)) << 14;
			break;
		default:
			bus_addr |=  (0xf) << 14;
			break;
		}
	}

	val32 = readl(bus_addr);
	switch (len) {
	case 1:
		*val = (val32 >> (bo * 8)) & 0xff;
		break;
	case 2:
		*val = (val32 >> (bo * 8)) & 0xffff;
		break;
	default:
		*val = val32;
		break;
	}
#ifdef DEBUG_PCIE
		printf("pcie_read_config:  %s: cfg_data=%08x offset=%08x, bus_addr = 0x%08x, val = 0x%08x\n",
		       __func__, hose->cfg_data, offset, bus_addr, *val);
#endif


	return 0;
}

/* Write the configuration space */
static int pcie_write_config(struct pci_controller *hose, unsigned int devfn,
	int offset, int len, u32 val) {
	u8 *address;
	u64 bus_addr;
	u32 val32;

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

	address = pcie_get_base(hose, devfn);
	if (address == NULL)
		return 0;
#ifdef DEBUG_PCIE
	printf("pcie_write_config:  cfg space base_address  = 0x%x, cfg_data = 0x%x\n",
	       address, hose->cfg_data);
#endif

    /*
     * addressing is different for local config access vs.
     * access through the mapped config space. We need to
     * translate the offset for mapped config access
     */

	if (PCI_BUS(devfn) == 0) {
		/* the local ACP RC only supports 32-bit dword config access,
		 * so if this is a byte or 16-bit word access we need to
		 * perform a read-modify write
		 */
		if (len == 4) {
			bus_addr = (u64)address + offset;
		} else {
			int bs = ((offset & 0x3) * 8);
			bus_addr = (u64)address + (offset & 0xfffffffc);
			val32 = readl(bus_addr);

			if (len == 2)
				val32 = (val32 & ~(0xffff << bs))
					| ((val & 0xffff) << bs);
			else
				val32 = (val32 & ~(0xff << bs))
					| ((val & 0xff) << bs);
			val = val32;
			len = 4;
		}
	} else {
		bus_addr = (u64)address + (offset << 2) + (offset & 0x3);
	}
	switch (len) {
	case 1:
		writeb(val, (u8 *)(bus_addr));
		break;
	case 2:
		writew(val, (u16 *)(bus_addr));
		break;
	default:
		writel(val, (u32 *)(bus_addr));
		break;
	}

	return 0;
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

int pci_axxia_init(struct pci_controller *hose, int port)
{
	void *mbase = NULL;
	u32 pci_config, pci_status, link_state;
	int i, num_pages;
	u32 mpage_lower, pciah, pcial;
	u64 pci_addr, size;
	void __iomem *tpage_base;
	pci_addr_t bus_start = 0;   /* Start on the bus */
	phys_addr_t phys_start = 0;
	unsigned pci_link;

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
		mbase = (u64 *)CONFIG_SYS_PCIE0_CFGADDR;
		hose->cfg_data = (u8 *)CONFIG_SYS_PCIE0_MEMBASE;
		bus_start = CONFIG_PCIE0_BUS_START;
		phys_start = CONFIG_PCIE0_PHY_START;
		break;
	case 1:
		printf("PEI1 Root Complex.\n");
		/* PEI1 RC Mode */
		mbase = (u64 *)CONFIG_SYS_PCIE1_CFGADDR;
		hose->cfg_data = (u8 *)CONFIG_SYS_PCIE1_MEMBASE;
		bus_start = CONFIG_PCIE1_BUS_START;
		phys_start = CONFIG_PCIE1_PHY_START;
		break;
	case 2:
		printf("PEI2 Root Complex.\n");
		/* PEI2 RC Mode */
		mbase = (u64 *)CONFIG_SYS_PCIE2_CFGADDR;
		hose->cfg_data = (u8 *)CONFIG_SYS_PCIE2_MEMBASE;
		bus_start = CONFIG_PCIE2_BUS_START;
		phys_start = CONFIG_PCIE2_PHY_START;
		break;
	}

	/* We only get here if we are RC mode for either PEI0 or PEI1 */

	hose->cfg_addr = mbase;
#ifdef DEBUG_PCIE
	printf("port = %d, hose = 0x%x, hose->cfg_addr = 0x%x\n",
	       port, hose, mbase);
#endif
	tpage_base = mbase + 0x1050;
	pci_addr = bus_start;
	pciah = U64_TO_U32_HIGH(pci_addr);
	pcial = U64_TO_U32_LOW(pci_addr);

	hose->first_busno = 0x0;
	hose->current_busno = 0x0;
	hose->last_busno = 0xff;

	pci_set_region(hose->regions + 0,
		       0x0,
		       0x0,
		       (1024*1024),
		       PCI_REGION_MEM);
	hose->region_count = 1;

	/* Check if setup as root complex */
	pci_config = readl(mbase + 0x1000);
	pci_status = readl(mbase + 0x1004);
	printf("PEI%d pci_status = 0x%x\n", port, pci_status);
	if ((pci_status & 0x10) != 0x10) {
		printf("PEI%d is set up as EP\n", port);
		return 0;
	}

	link_state = (pci_status & 0x3f00) >> 8;
	printf("PCIE status = 0x%08x : PCI link state = 0x%x\n",
	       pci_status, link_state);

	/* make sure the link is up */
	if (link_state != 0xb) {
		/* reset */
		printf("PCI link in bad state - resetting\n");
		pci_config |= 1;
		writel(pci_config, mbase + 0x1000);
		udelay(1000000);

		pci_status = readl(mbase + 0x1004);
		link_state = (pci_status & 0x3f00) >> 8;
	}
	printf("PCI link state now = 0x%x\n", link_state);
	if (link_state != 0xb) {
		/* return since link state is not okay */
		return 0;
	}

	/* Read the "PEI Link Speed Change Command and Link Status" register */
	pci_link = readl(mbase + 0x117c);

	printf("PEI%d: x%d @ ", port, ((pci_link & 0x3f0) >> 4));
	switch (pci_link & 0xF) {
	case 1:
		printf("2.5Gbps\n");
		break;
	case 2:
		printf("5Gbps\n");
		break;
	}

	/* setup ACP for 4GB 1=Prefetchable, 10=Locate anywhere in
	 * 64 bit address space */
	/* configures the RC Memory Space Configuration Register */
	writel(0x40000000, mbase + 0x11f4);

	/* Verify BAR0 size */
	{
		u32 bar0_size;
		/* write all 1s to BAR0 register */
		writel(~0, mbase + 0x10);
		bar0_size = readl(mbase + 0x10);
		if ((bar0_size & ~0xf) != 0x40000000)
			printf("PCIE%d: Config BAR0 failed\n", port);
	}

	/* set the BASE0 address to start of PCIe base 0x0 */
	writel(0x0, mbase + 0x10);

	/* setup TPAGE registers for inbound mapping */
	/* We set the MSB of each TPAGE to select 128-bit AXI access.
	 * For the address field we simply program an incrementing value
	 * to map consecutive pages
	 */
	tpage_base = mbase + 0x1050;
	for (i = 0; i < 8; i++) {
		writel((0x80000000 + i), tpage_base);
		tpage_base += 4;
	}

	/* ACP X1 setup MPAGE registers */
	/*
	 * MPAGE7 is dedicated to config access, so we only
	 * have 7 128MB pages available for memory i/o.
	 * Calculate how many pages we need
	 */
	size = 7 * 1024*128*1024;
	num_pages = ((size - 1) >> 27) + 1;
	for (i = 0; i < num_pages; i++) {
		mpage_lower = (pcial & 0xf8000000);
		writel(pciah, mbase + ACPX1_PCIE_MPAGE_UPPER(i));
		writel(mpage_lower, mbase + ACPX1_PCIE_MPAGE_LOWER(i));
		pcial += 0x08000000;
	}

	hose->last_busno = pci_hose_scan(hose);

	printf("PCIE%d: successfully set as root-complex\n", port);
	pci_set_region(hose->regions + 0,
		       bus_start,
		       phys_start,
		       (1024*1024*1024),
		       PCI_REGION_MEM);

	hose->region_count = 1;
	pci_register_hose(hose);
#ifdef DEBUG_PCIE
	printf("pci_axxia_init: Returned bus no after = %d\n",
	       hose->last_busno);
#endif
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
