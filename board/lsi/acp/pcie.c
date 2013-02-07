#include <common.h>
#include <command.h>
#include <asm/4xx_pci.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <pci.h>

#undef DEBUG_PCIE
//#define DEBUG_PCIE

#if (defined(CONFIG_ACP)) 
#include <asm/4xx_pcie.h>
#endif

#if defined (ACP_25xx)
#include "regs/ncp_denali_regs_acp2500.h"
#include "regs/ncp_denali_reg_defines_acp2500.h"
#include "regs/ncp_phy_regs_acp2500.h"
#include "regs/ncp_phy_reg_defines_acp2500.h"
#endif


#ifdef CONFIG_PCI

#ifdef CONFIG_ACP3

#define ACPX1_PCIE_MPAGE_UPPER(n) (0x1010 + (n * 8))
#define ACPX1_PCIE_MPAGE_LOWER(n) (0x1014 + (n * 8))

static struct pci_controller ppc476_hose[CONFIG_SYS_PCIE_NR_PORTS];


/* Check if the PEI is been setup as end point */
static int validate_endpoint(struct pci_controller *hose)
{

	if (hose->cfg_data == (u8 *)CONFIG_SYS_PCIE0_MEMBASE)
		return (is_end_point(0));
	else if (hose->cfg_data == (u8 *)CONFIG_SYS_PCIE1_MEMBASE)
		return (is_end_point(1));
#if CONFIG_SYS_PCIE_NR_PORTS > 2
	else if (hose->cfg_data == (u8 *)CONFIG_SYS_PCIE2_MEMBASE)
		return (is_end_point(2));
#endif
	return 0;
}

/* get the base address of the configuration space */
static u8* pcie_get_base(struct pci_controller *hose, unsigned int devfn)
{
	u8 *base = (u8*)hose->cfg_data;
	int dev,fn;
	int cfg_type=0;
	u32 addr;
	unsigned mpage;
	int relbus;

	//hose->cfg_addr = (u32 *)CONFIG_SYS_PCIE0_CFGADDR;
	if (PCI_BUS(devfn) == 0) {
		return((u8 *)hose->cfg_addr);
	} else {
		dev = PCI_DEV(devfn);
		fn = PCI_FUNC(devfn);

		if (dev > 31) 
			return NULL;

#if defined(ACP_X1V1)
		/* v1 only supports fn=0 */
		if (fn)
			return NULL;
#elif defined(ACP_X1V2) || defined(CONFIG_ACP_342X)
		/* v2 only supports fn0-3 and bus0-63 */
		if ((fn > 3) || (PCI_BUS(devfn) > 63)) 
			return NULL;
#endif

		/* Primary bus */
		if (PCI_BUS(devfn) == 1) {
			cfg_type = 0;
		} else {
			cfg_type = 1;
		}
#ifdef DEBUG_PCIE
		printf("pcie_get_base: bus = %d -- cfg type = %d\n", PCI_BUS(devfn), cfg_type);
#endif

		/* build the mpage register */
		mpage = (PCI_BUS(devfn) << 11) |
		(dev << 6) |
		(cfg_type << 5);

		/* the function number moved for X2 */
#if defined(ACP_X1V1) || defined(ACP_X1V2)
		mpage |= 0x11;	/* enable MPAGE for configuration access */
		mpage |= (fn << 17);
#else
		mpage |= 0x10;	/* enable MPAGE for configuration access */
		mpage |= (fn << 19);
#endif

		addr = ((u32)hose->cfg_addr) + ACPX1_PCIE_MPAGE_UPPER(7);
		out_le32((u32 *) addr, 0x0);
		addr = ((u32)hose->cfg_addr) + ACPX1_PCIE_MPAGE_LOWER(7);
#ifdef DEBUG_PCIE
		printf("pcie_get_base: %02x:%02x:%02x setting mpage = 0x%08x in addr = 0x%08x\n", PCI_BUS(devfn), dev, fn, mpage, addr); 	
#endif
		out_le32((u32 *) addr, mpage);
	}
		
	return base;
}

/* Read the configuration space */
static int pcie_read_config(struct pci_controller *hose, unsigned int devfn, 
	int offset, int len, u32 *val) {

	u8 *address;
	*val = 0;
	u32 bus_addr, val32, mcsr;
	int bo = offset & 0x3;
	int wo;

	if (validate_endpoint(hose))
		return 0;		/* No upstream config access */

	/*
	 * NOTICE: configuration space ranges are currently mapped only for
	 * the first 16 buses, so such limit must be imposed. In case more
	 * buses are required the TLB settings in board/amcc/<board>/init.S
	 * need to be altered accordingly (one bus takes 1 MB of memory space).
	 */
	if (PCI_BUS(devfn) >= 16) {
		return 0;
	}

	/*
	 * Only single device/single function is supported for the primary and
	 * secondary buses of the 440SPe host bridge.
	 */
	if (((!((PCI_FUNC(devfn) == 0) && (PCI_DEV(devfn) == 0))) &&
		(PCI_BUS(devfn) == 0)) || (!(PCI_DEV(devfn) == 0) &&
                (PCI_BUS(devfn) == 1))) {
		return 0;
	}

	address = pcie_get_base(hose, devfn);
	if (address == NULL)
		return 0;
#ifdef DEBUG_PCIE
	printf("pcie_read_config:  cfg space base_address  = 0x%x, cfg_data = 0x%x\n", address, hose->cfg_data);
#endif

        /*
         * Reading from configuration space of non-existing device can
         * generate transaction errors. For the read duration we suppress
         * assertion of machine check exceptions to avoid those.
         */
        mtmsr( mfmsr() & ~(MSR_ME));
        __asm__ __volatile__("msync");


	if (PCI_BUS(devfn) == 0) {
		wo = offset & 0xfffffffc;
		bus_addr = (u32)address+wo;
	} else {
		/* 
		 * mapped config space only supports 32-bit access 
		 *  AXI address [3:0] is not used at all.  
		 *  AXI address[9:4] becomes register number.  
		 *  AXI address[13:10] becomes Ext. register number 
		 *  AXI address[17:14] becomes 1st DWBE for configuration read only.  
		 *  AXI address[29:27] is used to select one of 8 Mpage registers.  
		 */
		bus_addr = (u32) address + (offset << 2);

		switch (len) {
			case 1:
				bus_addr |=  ((1 << bo) ) << 14;
				break;
			case 2:
				bus_addr |=  ((3 << bo) ) << 14;
				break;
			default:
				bus_addr |=  ( 0xf ) << 14;
				break;
		}
	}

	val32 = in_le32((u32 *)bus_addr);
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
	 __asm__ __volatile__("msync");
	mcsr = mfspr(SPRN_MCSR);
	if ( mcsr != 0) {
		mtspr(SPRN_MCSR, 0);
		__asm__ __volatile__("msync");	

#ifdef DEBUG_PCIE
		printf("pcie_read_config:  %s: cfg_data=%08x offset=%08x, bus_addr = 0x%08x machine check!! val = 0x%08x\n", __func__, hose->cfg_data, offset, bus_addr, mcsr);
#endif
		*val = 0;
	} else {

#ifdef DEBUG_PCIE
		printf("pcie_read_config:  %s: cfg_data=%08x offset=%08x, bus_addr = 0x%08x, val = 0x%08x\n", __func__, hose->cfg_data, offset, bus_addr, *val);
#endif
	}
	/* re-enable machine checks */
	mtmsr(mfmsr() | (MSR_ME) );
	__asm__ __volatile__("msync");


	return 0;
}

/* Write the configuration space */
static int pcie_write_config(struct pci_controller *hose, unsigned int devfn,
	int offset, int len, u32 val) {

	u8 *address;
	u32 bus_addr, val32;
	int bo = offset & 0x3;
	int wo;


	if (validate_endpoint(hose))
		return 0;		/* No upstream config access */

	/*
	 * Same constraints as in pcie_read_config().
	 */
	if (PCI_BUS(devfn) >= 16)
		return 0;

	if (((!((PCI_FUNC(devfn) == 0) && (PCI_DEV(devfn) == 0))) &&
		(PCI_BUS(devfn) == 0)) || (!(PCI_DEV(devfn) == 0) &&
                (PCI_BUS(devfn) == 1))) {
		return 0;
	}

	address = pcie_get_base(hose, devfn);
	if (address == NULL)
		return 0;
#ifdef DEBUG_PCIE
	printf("pcie_write_config:  cfg space base_address  = 0x%x, cfg_data = 0x%x\n", address, hose->cfg_data);
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
			bus_addr = (u32) address + offset;
		} else {
			int bs = ((offset & 0x3) * 8);
			bus_addr = (u32) address + (offset & 0xfffffffc);
			val32 = in_le32((u32 *)bus_addr);

			if (len == 2) {
				val32 = (val32 & ~(0xffff << bs) ) | ((val & 0xffff) << bs);
			} else {
				val32 = (val32 & ~(0xff << bs) ) | ((val & 0xff) << bs);
			}
			val = val32;
			len = 4;
		}
	} else {
		bus_addr = (u32) address + (offset << 2) + (offset & 0x3);
	}
	switch (len) {
		case 1:
			out_8((u8 *)(bus_addr), val);
			break;
		case 2:
			out_le16((u16 *)(bus_addr), val);
			break;
		default:
			out_le32((u32 *)(bus_addr), val);
			break;
	}

	return 0;
}

int pcie_read_config_byte(struct pci_controller *hose,pci_dev_t dev,int offset,u8 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 1, &v);
	*val = (u8)v;
	return rv;
}

int pcie_read_config_word(struct pci_controller *hose,pci_dev_t dev,int offset,u16 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 2, &v);
	*val = (u16)v;
	return rv;
}

int pcie_read_config_dword(struct pci_controller *hose,pci_dev_t dev,int offset,u32 *val)
{
	u32 v;
	int rv;
	rv = pcie_read_config(hose, dev, offset, 4, &v);
	*val = (u32)v;
	return rv;
}

int pcie_write_config_byte(struct pci_controller *hose,pci_dev_t dev,int offset,u8 val)
{
	return pcie_write_config(hose,(u32)dev,offset,1,val);
}

int pcie_write_config_word(struct pci_controller *hose,pci_dev_t dev,int offset,u16 val)
{
	return pcie_write_config(hose,(u32)dev,offset,2,(u32 )val);
}

int pcie_write_config_dword(struct pci_controller *hose,pci_dev_t dev,int offset,u32 val)
{
	return pcie_write_config(hose,(u32)dev,offset,4,(u32 )val);
}

int pci_476_init (struct pci_controller *hose, int port)
{
	volatile void *mbase = NULL;
	u32 pci_config, pci_status, link_state;
	int i, num_pages;
	u32 mpage_lower, pciah, pcial;
	u64 pci_addr, plb_addr, size, flags;
	void __iomem *tpage_base;
	pci_addr_t bus_start;   /* Start on the bus */
	phys_addr_t phys_start;
	unsigned long registers;

	pci_set_ops(hose, 
		pcie_read_config_byte, 
		pcie_read_config_word, 
		pcie_read_config_dword, 
		pcie_write_config_byte, 
		pcie_write_config_word, 
		pcie_write_config_dword); 

	switch (port) {
		case 0:
#if defined (ACP_25xx)
			ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &registers);
			if (registers & 0x400001) {
				/* PEI0 RC mode */
				mbase = (u32 *)CONFIG_SYS_PCIE0_CFGADDR;
				hose->cfg_data = (u8 *)CONFIG_SYS_PCIE0_MEMBASE;
				bus_start = CONFIG_PCIE0_BUS_START;
				phys_start = CONFIG_PCIE0_PHY_START;
				break;
			} else {
				return 0;
			}
#endif
			/* PEI0 RC mode */
			mbase = (u32 *)CONFIG_SYS_PCIE0_CFGADDR;
			hose->cfg_data = (u8 *)CONFIG_SYS_PCIE0_MEMBASE;
			bus_start = CONFIG_PCIE0_BUS_START;
			phys_start = CONFIG_PCIE0_PHY_START;
			break;
        case 1:
#if defined (ACP_25xx)
			ncr_read32(NCP_REGION_ID(0x115, 0), 0x200, &registers);
			if (registers & 0x2) {
				/* PEI1 enabled */
				mbase = (u32 *)CONFIG_SYS_PCIE1_CFGADDR;
				hose->cfg_data = (u8 *)CONFIG_SYS_PCIE1_MEMBASE;
				bus_start = CONFIG_PCIE1_BUS_START;
				phys_start = CONFIG_PCIE1_PHY_START;
				break;
			} else
				return 0;
#endif
			mbase = (u32 *)CONFIG_SYS_PCIE1_CFGADDR;
			hose->cfg_data = (u8 *)CONFIG_SYS_PCIE1_MEMBASE;
			bus_start = CONFIG_PCIE1_BUS_START;
			phys_start = CONFIG_PCIE1_PHY_START;
			break;
#if CONFIG_SYS_PCIE_NR_PORTS > 2
        case 2:
			mbase = (u32 *)CONFIG_SYS_PCIE2_CFGADDR;
			hose->cfg_data = (u8 *)CONFIG_SYS_PCIE2_MEMBASE;
			bus_start = CONFIG_PCIE2_BUS_START;
			phys_start = CONFIG_PCIE2_PHY_START;
			break;
#endif
	}
	hose->cfg_addr = mbase;
#ifdef DEBUG_PCIE
	printf("port = %d, hose = 0x%x, hose->cfg_addr = 0x%x\n", port, hose,mbase);
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
		
	/* setup as root complex */
	pci_config = in_le32(mbase + 0x1000);
	pci_status = in_le32(mbase + 0x1004);
	link_state = (pci_status & 0x3f00) >> 8;
	printf("PCIE status = 0x%08x : PCI link state = 0x%x\n", pci_status, link_state);

	/* make sure the link is up */
	if (link_state != 0xb) {
		/* reset */
		printf("PCI link in bad state - resetting\n");
		pci_config |= 1;
		out_le32(mbase + 0x1000, pci_config);
		udelay(1000000); 

		pci_status = in_le32(mbase + 0x1004);
		link_state = (pci_status & 0x3f00) >> 8;
	}
	printf("PCI link state now = 0x%x\n", link_state); 
	if (link_state != 0xb) {
		/* return since link state is not okay */
		return 0;
	}

	/*
	 * for v2 we need to set the 'axi_interface_rdy' bit
	 * this bit didn't exist in X1V1, and means something
	 * else for X2...
	 */
#if defined (ACP_X1V2)
	/* set up AXI_INTERFACE_RDY */
	pci_config = in_le32(mbase + 0x1000);
	out_le32(mbase + 0x1000, pci_config|0x40000);
	pci_config = in_le32(mbase + 0x1000);
#endif 
	
	/* setup ACP for 4GB 1=Prefetchable, 10=Locate anywhere in
	 * 64 bit address space */
	out_le32(mbase + 0x10, 0x1000000c);
	out_le32(mbase + 0x14, 0x0); 

	out_8(hose->cfg_data + PCI_PRIMARY_BUS, hose->first_busno);
	out_8(hose->cfg_data + PCI_SECONDARY_BUS, hose->first_busno + 1);
	out_8(hose->cfg_data + PCI_SUBORDINATE_BUS, hose->last_busno); 

	/* ACP X1 setup MPAGE registers */ 
	/*
	 * MPAGE7 is dedicated to config access, so we only 
	 *  have 7 128MB pages available for memory i/o. 
	 *  Calculate how many pages we need
	 */
	size = 7 * 1024*128*1024;
	num_pages = ( (size - 1) >> 27) + 1;
	for (i = 0; i < num_pages; i++) {
		mpage_lower = (pcial & 0xf8000000); 
#if defined(ACP_X1V1) || defined(ACP_X1V2)
		mpage_lower |= 1;
#endif
		out_le32( mbase + ACPX1_PCIE_MPAGE_UPPER(i), pciah);
		out_le32( mbase + ACPX1_PCIE_MPAGE_LOWER(i), mpage_lower);
		pcial += 0x08000000;
	} 
	for (i = 0; i < 8; i++) {
		out_le32(tpage_base, (0x80000000 + i));
		tpage_base += 4;
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
	printf("pci_476_init: Returned bus no after = %d\n", hose->last_busno);
#endif
	hose->first_busno = 0;
	hose->current_busno = hose->last_busno+1;
	hose->last_busno = 0xff;
	hose->last_busno = pci_hose_scan(hose);

	return hose->last_busno;
}

void pci_init_board(void)
{
	unsigned long word0;
	unsigned long word1;
	unsigned long word2;
	int busno;

#if defined(ACP_PEI0) && defined(ACP_PEI1) && defined(ACP_PEI2)

	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 0
	 * and MPAGE7 1 MB config space
	 * 0x0020_4000_0000 to 0x0020_7FFF_FFFF */

	word0 = 0x20000000 | 0x9f0;
	word1 = 0x40000020;
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x30000000 | 0x8f0;
	word1 = 0x78000020;
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	busno = pci_476_init (&ppc476_hose[0], 0);


	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 1
	 * and MPAGE7 1 MB config space
	 * 0x0020_c000_0000 to 0x0020_FFFF_FFFF */

	word0 = 0x40000000 | 0x9f0;
	word1 = 0xc0000020;
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x50000000 | 0x8f0;
	word1 = 0xf8000020;
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	busno = pci_476_init (&ppc476_hose[1], 1);

	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 2
	 * and MPAGE7 1 MB config space
	 * 0x0021_0000_0000 to 0x0021_3FFF_FFFF */

	word0 = 0x60000000 | 0x9f0;
	word1 = 0x00000021;
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x70000000 | 0x8f0;
	word1 = 0x38000021;
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	busno = pci_476_init (&ppc476_hose[2], 2);
#elif defined(ACP_PEI0) && defined(ACP_PEI1)
	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 0
	 * and MPAGE7 1 MB config space
	 * 0x0020_4000_0000 to 0x0020_7FFF_FFFF */

	word0 = 0x20000000 | 0x9f0;
	word1 = 0x40000020;
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x30000000 | 0x8f0;
	word1 = 0x78000020;
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	
	busno = pci_476_init (&ppc476_hose[0], 0);

	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 1
	 * and MPAGE7 1 MB config space
	 * 0x0020_c000_0000 to 0x0020_FFFF_FFFF */

	word0 = 0x40000000 | 0x9f0;
#if defined (ACP_25xx)
	word1 = 0x80000020;
#else
	word1 = 0xc0000020;
#endif
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x50000000 | 0x8f0;
#if defined (ACP_25xx)
	word1 = 0xb8000020;
#else
	word1 = 0xf8000020;
#endif
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	busno = pci_476_init (&ppc476_hose[1], 1);
#elif defined(ACP_PEI0)

	/* create tlb entry for 256MB  PCIe space for 2 MPAGEs of port 0
	 * and MPAGE7 1 MB config space
	 * 0x0020_4000_0000 to 0x0020_7FFF_FFFF */

	word0 = 0x40000000 | 0xbf0;
	word1 = 0x40000020;
	word2 = 0x00030507;

	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \ 
			"tlbwe %2,%0,1\n"               \ 
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );

	word0 = 0x78000000 | 0x8f0;
	word1 = 0x78000020;
	word2 = 0x00030507;
	__asm__ __volatile__ ( "tlbwe %1,%0,0\n"               \
			"tlbwe %2,%0,1\n"               \
			"tlbwe %3,%0,2\n"               \
			"isync\n" : :
			"r" (0x80000000),
			"r" (word0),
			"r" (word1),
			"r" (word2) :
			"memory" );
	busno = pci_476_init (&ppc476_hose[0], 0);
#endif


}


#endif /* CONFIG_ACP3 */

#endif /* CONFIG_PCI */
