/*
 * Axxia NEMAC 10/100/1000 Ethernet Controller
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <command.h>
#include <net.h>
#include <exports.h>
#include <asm/io.h>
#include <asm/cache.h>
#include <miiphy.h>
#include <phy.h>

DECLARE_GLOBAL_DATA_PTR;

#define DESCRIPTOR_GRANULARITY	64
#define BUFFER_GRANULARITY	64
#define TX_RING_SIZE		(1 * DESCRIPTOR_GRANULARITY)
#define RX_RING_SIZE		PKTBUFSRX
#define MDIO_DEV		"axxia-mdio"

#define NEM_VERSION_R			0x0000
#define    MAJOR_REV(_x)		(((_x) >> 24) & 0xff)
#define    MINOR_REV(_x)		(((_x) >> 16) & 0xff)
#define NEM_PRESENCE_R			0x0008
#define    PRESENT_GMAC0		(1 << 0)
#define    PRESENT_GMAC0_PFC		(1 << 16)
#define NEM_INT_STATUS_R		0x0010
#define NEM_INT_ENABLE_R		0x0014
#define NEM_INT_FORCE_R			0x0018
#define    INT_GROUP_GMAC0		(1 << 0)
#define    INT_GROUP_STATS		(1 << 14)
#define    INT_GROUP_PTI		(1 << 15)
#define NEM_SWRESET_R			0x0020
#define    SWRESET_GMAC0		(1 << 0)
#define    SWRESET_STATS		(1 << 14)
#define    SWRESET_PTI			(1 << 15)
#define NEM_ACTIVE_R			0x0024
#define    ACTIVE_GMAC0			(1 << 0)
#define NEM_GMAC_ENABLE_R		0x0300
#define    MAC_PAUSE_QUANTA(_x)		(((_x) & 0xffff) << 16)	 /* 0..65535 */
#define    RGMII_SWAP_TX		(1 << 9)
#define    RGMII_SWAP_RX		(1 << 8)
#define    RGMII_MODE			(1 << 7)
#define    GPIO_CLK_MUX_SELECT		(1 << 6)
#define    GMAC_TX_INIT_PAUSE		(1 << 5)
#define    GMII_BYPASS_MODE		(1 << 4)
#define    GMAC_RX_EN			(1 << 3)
#define    PORT_ENABLE			(1 << 2)
#define    GMAC_RX_PAUSE_EN		(1 << 1)
#define    GMAC_TX_PAUSE_EN		(1 << 0)
#define NEM_GMAC_STA_ADDR_R		0x0304
#define NEM_GMAC_STA_ADDR_UPPER_R	0x0308
#define NEM_GMAC_TIMING_CTRL_R		0x030c
#define    LOOPBACK_IFG_MODE		(1 << 6)
#define    SEL_EXT_PAUSE_WAIT_IN	(1 << 5)
#define    INFINITE_RETRY		(1 << 4)
#define    ZERO_BACKOFF			(1 << 3)
#define    FAST_SLOT_TMR_MODE		(1 << 2)
#define    FIXED_MODE			(1 << 1)
#define    SHORT_IFG_MODE		(1 << 0)
#define NEM_GMAC_MAC_CTRL_R		0x0310
#define    WOL_ENABLE			(1 << 10)
#define    TX_PAD_ENABLE		(1 << 6)
#define    RX_CRC_STRIP_ENABLE		(1 << 5)
#define    RX_ABORT_DISABLE		(1 << 4)
#define    GMAC_TX_FLUSH		(1 << 2)
#define    AUTO_FLUSH_MODE		(1 << 1)
#define    GM_DEBUG_SELECT		(1 << 0)
#define NEM_GMAC_MAC_STATUS_R		0x0314
#define    GM_DEBUG(_x)			(((_x) & 0x3ff) << 3)	 /* 0..1023 */
#define    L_FIFO_OVERRUN		(1 << 2)
#define    L_ANY_FIFO_UNDERRUN		(1 << 1)
#define    TX_ENCAP_DONE		(1 << 0)
#define NEM_GMAC_PRBS_ERR_R		0x0318
#define    C6_PRBS_ERR(_x)		(((_x) & 0xff) << 0)	 /* 0..255 */
#define NEM_GMAC_SGMII_ENABLE_R		0x031c
#define    SGMII_C73_INT_DISABLE	(1 << 2)
#define    SGMII_C37_INT_DISABLE	(1 << 1)
#define    SGMII_PORT_EN		(1 << 0)
#define NEM_GMAC_PRBS_CTRL_R		0x0320
#define    CLK_625_PATTERN_55		(1 << 26)
#define    CLK_625_PATTERN_AA		(1 << 25)
#define    LOOP_BACK			(1 << 24)
#define    RESET_PRBS_COUNTER		(1 << 23)
#define    INV_COMPARE			(1 << 22)
#define    LOAD_SEED			(1 << 21)
#define    PRBS_SEED(_x)		(((_x) & 0x3ff) << 11)	 /* 0..1023 */
#define    PRBS_DATA(_x)		(((_x) & 0x3ff) << 1)	 /* 0..1023 */
#define    PRBS_ENABLE			(1 << 0)
#define NEM_GMAC_ANEG_CTRL_R		0x0324
#define    SGMII_CLOCK_RATE		(1 << 13)
#define    IGNORE_AN_SYNC_STATUS	(1 << 12)
#define    IGNORE_RUDI_INVALID		(1 << 11)
#define    FIBER_MODE			(1 << 10)
#define    SGMII_GMAC_RX_PAUSE_EN	(1 << 9)
#define    SGMII_GMAC_FLOW_CONTROL_INITIATE_EN			(1 << 8)
#define    AUTONEG_OFFLINE_ADVERTISE	(1 << 7)
#define    AUTONEG_SPEED_UP		(1 << 6)
#define    SPEED_MODE_FORCE(_x)		(((_x) & 0x3) << 4)	 /* 0..3 */
#define    GOOD_LINK_FORCE		(1 << 3)
#define    FULL_DUPLEX_FORCE		(1 << 2)
#define    MR_AUTONEG_ENABLE		(1 << 1)
#define    RESTART_AUTONEG		(1 << 0)
#define NEM_GMAC_ANEG_STATUS_R		0x0328
#define    WOL				(1 << 13)
#define    C10_GMII_SPEED_MODE(_x)	(((_x) & 0x3) << 11)	 /* 0..3 */
#define    C10_GMII_FULL_DUPLEX		(1 << 10)
#define    GMII_LINK_OK			(1 << 9)
#define    AUTONEG_TX_PAUSE_EN		(1 << 8)
#define    AUTONEG_RX_PAUSE_EN		(1 << 7)
#define    REMOTE_FAULT(_x)		(((_x) & 0x3) << 5)	 /* 0..3 */
#define    REMOTE_PAUSE(_x)		(((_x) & 0x3) << 3)	 /* 0..3 */
#define    REMOTE_HD_FD(_x)		(((_x) & 0x3) << 1)	 /* 0..3 */
#define    MR_AN_COMPLETE		(1 << 0)
#define NEM_GMAC_SGMII_STATUS_R		0x032c
#define    SGMII_FULL_DUPLEX		(1 << 13)
#define    SGMII_SPEED_MODE(_x)		(((_x) & 0x3) << 11)	 /* 0..3 */
#define    SGMII_LINK			(1 << 10)
#define    SYNC_STATUS			(1 << 9)
#define    RX_DV			(1 << 8)
#define    C11_PRBS_ERR			(1 << 7)
#define    CURRENT_AUTONEG_STATE(_x)	(((_x) & 0x7) << 4)	 /* 0..7 */
#define    C11_GMII_FULL_DUPLEX		(1 << 3)
#define    C11_GMII_SPEED_MODE(_x)	(((_x) & 0x3) << 1)	 /* 0..3 */
#define    GMII_LINK			(1 << 0)
#define NEM_GMAC_FILTER_CTRL_R		0x0330
#define    ENABLE_BLANKET_FILTERING	(1 << 7)
#define    ENABLE_UNICAST_SA_FILTERING	(1 << 6)
#define    ENABLE_RUNT_FILTERING	(1 << 5)
#define    ENABLE_PAUSE_FILTERING	(1 << 4)
#define    ENABLE_UNICAST_FILTERING	(1 << 3)
#define    ENABLE_MULTICAST_FILTERING	(1 << 2)
#define    ENABLE_BROADCAST_FILTERING	(1 << 1)
#define    PACKET_FILTERING_ENABLE	(1 << 0)
#define NEM_GMAC_MULTICAST_R(_x)	(0x0334 + (_x) * 4)
#define NEM_GMAC_UNICAST1_R		0x0344
#define NEM_GMAC_UNICAST2_R		0x0348
#define NEM_GMAC_UNICAST12_UPPER_R	0x034c
#define    UNICAST_ADDRESS_1_UPPER(_x)	(((_x) & 0xffff) << 0)
#define    UNICAST_ADDRESS_2_UPPER(_x)	(((_x) & 0xffff) << 16)
#define NEM_GMAC_UNICAST3_R		0x0350
#define NEM_GMAC_UNICAST3_UPPER_R	0x0354
#define    UNICAST_ADDRESS_3_UPPER(_x)	(((_x) & 0xffff) << 0)
#define NEM_GMAC_C37_ANEG_INT_MASK_R	0x0360
#define    WOL				(1 << 13)
#define    GMII_SPEED_MODE_MASK(_x)	(((_x) & 0x3) << 11)	 /* 0..3 */
#define    GMII_FULL_DUPLEX_MASK	(1 << 10)
#define    GMII_LINK_OK_MASK		(1 << 9)
#define    AUTONEG_TX_PAUSE_EN_MASK	(1 << 8)
#define    AUTONEG_RX_PAUSE_EN_MASK	(1 << 7)
#define    REMOTE_FAULT_MASK(_x)	(((_x) & 0x3) << 5)	 /* 0..3 */
#define    REMOTE_PAUSE_MASK(_x)	(((_x) & 0x3) << 3)	 /* 0..3 */
#define    REMOTE_HD_FD_MASK(_x)	(((_x) & 0x3) << 1)	 /* 0..3 */
#define    MR_AN_COMPLETE_MASK		(1 << 0)
#define NEM_GMAC_C73_ANEG_STATUS_R	0x0368
#define    LINK_STATUS_10GKR_CHANGE	(1 << 18)
#define    LINK_STATUS_10GKR		(1 << 17)
#define    LOSS_OF_SIGNAL_CHANGED	(1 << 16)
#define    AN_COMPLETE_CHANGED		(1 << 15)
#define    LINK_STATUS_10GKX4_CHANGE	(1 << 14)
#define    LINK_STATUS_1GKX_CHANGE	(1 << 13)
#define    AN_RESTART_FAULT		(1 << 12)
#define    AN_LINK_OK			(1 << 11)
#define    LOSS_OF_SIGNAL		(1 << 10)
#define    NONCE_FAILURE		(1 << 9)
#define    PARALLEL_DETECTION_FAULT	(1 << 8)
#define    PARALLEL_DETECTION_COMPLETE	(1 << 7)
#define    PAGE_RECEIVED		(1 << 6)
#define    AN_COMPLETE			(1 << 5)
#define    C26_REMOTE_FAULT		(1 << 4)
#define    AN_ABILITY			(1 << 3)
#define    LINK_STATUS_10GKX4		(1 << 2)
#define    LINK_STATUS_1GKX		(1 << 1)
#define    LP_AN_ABILITY		(1 << 0)
#define NEM_GMAC_C73_ANEG_INT_MASK_R	0x038c
#define    LINK_STATUS_10GKR_CHANGE_MASK	(1 << 18)
#define    LINK_STATUS_10GKR_MASK	(1 << 17)
#define    LOSS_OF_SIGNAL_CHANGED_MASK	(1 << 16)
#define    AN_COMPLETE_CHANGED_MASK	(1 << 15)
#define    LINK_STATUS_10GKX4_CHANGE_MASK	(1 << 14)
#define    LINK_STATUS_1GKX_CHANGE_MASK	(1 << 13)
#define    AN_RESTART_FAULT_MASK	(1 << 12)
#define    AN_LINK_OK_MASK		(1 << 11)
#define    LOSS_OF_SIGNAL_MASK		(1 << 10)
#define    NONCE_FAILURE_MASK		(1 << 9)
#define    PARALLEL_DETECTION_FAULT_MASK	(1 << 8)
#define    PARALLEL_DETECTION_COMPLETE_MASK	(1 << 7)
#define    PAGE_RECEIVED_MASK		(1 << 6)
#define    AN_COMPLETE_MASK		(1 << 5)
#define    C35_REMOTE_FAULT_MASK	(1 << 4)
#define    AN_ABILITY_MASK		(1 << 3)
#define    LINK_STATUS_10GKX4_MASK	(1 << 2)
#define    LINK_STATUS_1GKX_MASK	(1 << 1)
#define    LP_AN_ABILITY_MASK		(1 << 0)
#define NEM_GMAC_UCAST_MASK_LOWER_R	0x0394
#define NEM_GMAC_UCAST_MASK_UPPER_R	0x0398
#define NEM_GMAC_PFC_ENABLE_R		0x039c
#define    PLEVEL(_x)			(((_x) & 0xff) << 0)	 /* 0..255 */
#define NEM_GMAC_PFC_CONTROL_R		0x03a0
#define    ALLOW_UCAST			(1 << 8)
#define    SEND_PAUSE(_x)		(((_x) & 0xff) << 0)	 /* 0..255 */
#define NEM_GMAC_PFC_STATUS_R		0x03a4
#define    PAUSED(_x)			(((_x) & 0xff) << 0)	 /* 0..255 */
#define NEM_GMAC_IFG_MON_R		0x03b8
#define    EXCESS_IFG_FRAMES(_x)	(((_x) & 0xffff) << 16)	 /* 0..65535 */
#define    MIN_IFG(_x)			(((_x) & 0x3f) << 10)	 /* 0..63 */
#define    MAX_IFG(_x)			(((_x) & 0x3ff) << 0)	 /* 0..1023 */
#define NEM_DMA_CTL			0x3000
#define   DMACTL_RST			(1 << 31)
#define   DMACTL_EN			(1 << 16)
#define   DMACTL_ALLOW_TX_PAUSE		(1 << 15)
#define   DMACTL_FORCE_RX_ORDER		(1 << 14)
#define   DMACTL_TX_TAIL_PTR_EN		(1 << 13)
#define   DMACTL_RX_TAIL_PTR_EN		(1 << 12)
#define   DMACTL_AXI_BURST(_n)		((_n) <<  8)
#define   DMACTL_PTI_BURST(_n)		((_n) <<  4)
#define   DMACTL_ARB(_x)		((_x) <<  0)
#define      ARB_RR			0	/* Round robin */
#define      ARB_PRIO_RX		1	/* Prioritize receive */
#define      ARB_PRIO_TX		2	/* Prioritize transmit */
#define NEM_DMA_ENABLE			0x3004
#define   RXDMA_EN			(1<<17)
#define   TXDMA_EN			(1<<16)
#define NEM_DMA_RXQ_ADDR		0x3008
#define NEM_DMA_TXQ_ADDR		0x3010
#define NEM_DMA_RXQ_SIZE		0x3018
#define NEM_DMA_TXQ_SIZE		0x301c
#define NEM_DMA_RXTAIL_PTR_ADDR		0x3020
#define NEM_DMA_TXTAIL_PTR_ADDR		0x3028
#define NEM_DMA_RXHEAD_PTR		0x3030
#define NEM_DMA_TXHEAD_PTR		0x3034
#define NEM_DMA_AXI_CTL			0x3038
#define   AXICTL_ARPROT(_x)		((_x) << 12)
#define   AXICTL_ARCACHE(_x)		((_x) <<  8)
#define   AXICTL_AWPROT(_x)		((_x) <<  4)
#define   AXICTL_AWCACHE(_x)		((_x) <<  0)
#define NEM_DMA_MISC_CTL		0x303c
#define   MISCCTL_RGMII_1000		(0 << 0)
#define   MISCCTL_RGMII_100		(1 << 0)
#define   MISCCTL_RGMII_10		(2 << 0)
#define NEM_DMA_RXTAIL_PTR		0x3080
#define NEM_DMA_TXTAIL_PTR		0x3084
#define NEM_DMA_STATUS			0x3088
#define NEM_DMA_INTL_STATUS		0x3100
#define   INTL_BAD_PARAM		(1 << 0)
#define NEM_DMA_INTL_MASK		0x3104
#define NEM_DMA_INTL_INV		0x3108
#define NEM_DMA_INTL_NOMASK		0x310c
#define NEM_DMA_INTE_STATUS		0x3110
#define   INTE_RX_DONE			(1 << 9)
#define   INTE_TX_DONE			(1 << 8)
#define   INTE_ERR_MASK			0x7f
#define   INTE_RXDMA_WERR		(1 << 6)
#define   INTE_RXDMA_FIFO_ERR		(1 << 5)
#define   INTE_RXDESC_RERR		(1 << 4)
#define   INTE_TXDMA_RERR		(1 << 3)
#define   INTE_TXDMA_WERR		(1 << 2)
#define   INTE_TXDMA_FIFO_ERR		(1 << 1)
#define   INTE_TXDESC_RERR		(1 << 0)
#define NEM_DMA_INTE_MASK		0x3114
#define NEM_DMA_INTE_INV		0x3118
#define NEM_DMA_INTE_NOMASK		0x311c
#define NEM_DMA_INTE_RAW		0x3120

#define DMA_POINTER_GEN			0x100000
#define DMA_POINTER_MASK		0x0fffff
#define dmaptr_idx(_val) (((_val) & DMA_POINTER_MASK)/sizeof(struct dma_desc))
#define dmaptr_gen(_val) (!!((_val) & DMA_POINTER_GEN))

struct dma_desc {
	u32 ctrl;
#define DCTRL_SOP		(1 << 3)
#define DCTRL_EOP		(1 << 4)
#define DCTRL_INTR		(1 << 5)
#define DCTRL_RX_ERR		(1 << 6)
#define DCTRL_TX_NEGCRC		(1 << 6)
#define DCTRL_SWAP		(1 << 7)
#define DCTRL_TX_CRC		(1 << 8)
	u16 xfer_len;
	u16 pdu_len;
	u64 bufptr;
};

struct queue_ptr {
	u32 hw_tail;
	u32			tail;
	u32			head;
	u32			size;
	struct dma_desc	__iomem	*ring;
};

struct nemac_priv {
	struct eth_device	*dev;
	void __iomem		*reg;
	struct queue_ptr	rxq;
	struct queue_ptr	txq;
	struct mii_dev		*bus;
	struct phy_device	*phy_dev;
};

static struct dma_desc __iomem txring[TX_RING_SIZE] __aligned(64);
static struct dma_desc __iomem rxring[RX_RING_SIZE] __aligned(64);

static void
queue_init(struct queue_ptr *q, u32 num, void __iomem *ring, u32 hw_tail)
{
	q->hw_tail = hw_tail;
	q->head = hw_tail;
	q->tail = hw_tail;
	q->size = num * sizeof(struct dma_desc);
	q->ring = ring;
}

static inline struct dma_desc *
queue_get_head(const struct queue_ptr *q)
{
	if ((q->head ^ q->tail) == DMA_POINTER_GEN)
		return NULL;
	return &q->ring[dmaptr_idx(q->head)];
}

static inline struct dma_desc *
queue_get_tail(const struct queue_ptr *q)
{
	if (q->tail == q->hw_tail)
		return NULL;
	return &q->ring[dmaptr_idx(q->tail)];
}

static inline u32
inc_pointer(u32 ptr, u32 size)
{
	u32 newptr = (ptr & DMA_POINTER_MASK) + sizeof(struct dma_desc);

	/* When counter wraps (on size), reset and toggle generation bit.
	 * Otherwise preserve generation bit
	 */
	if (newptr >= size)
		newptr = (ptr & DMA_POINTER_GEN) ^ DMA_POINTER_GEN;
	else
		newptr |= ptr & DMA_POINTER_GEN;

	return newptr;
}

static inline u32
queue_inc_head(struct queue_ptr *q)
{
	q->head = inc_pointer(q->head, q->size);
	return q->head;
}

static inline u32
queue_inc_tail(struct queue_ptr *q)
{
	q->tail = inc_pointer(q->tail, q->size);
	return q->tail;
}

static inline void
pr_queue(const char *tag, const struct queue_ptr *q)
{
	debug("%s tail=%d.%lu hw_tail=%d.%lu head=%d.%lu\n",
	      tag,
	      dmaptr_gen(q->tail), dmaptr_idx(q->tail),
	      dmaptr_gen(q->hw_tail), dmaptr_idx(q->hw_tail),
	      dmaptr_gen(q->head), dmaptr_idx(q->head));
}

static inline void
pr_desc(const char *tag, const struct dma_desc *desc)
{
	debug("%s %p flags=%#x len=%u/%u buf=%#llx\n",
	      tag, desc,
	      le32_to_cpu(desc->ctrl),
	      le16_to_cpu(desc->xfer_len),
	      le16_to_cpu(desc->pdu_len),
	      le64_to_cpu(desc->bufptr));
}

static void
nemac_link_up(struct nemac_priv *priv, struct phy_device *phy_dev)
{
	u32 enable, ctrl, rgmii_clk;

	if (!phy_dev->link) {
		printf("%s: No link.\n", phy_dev->dev->name);
		return;
	}

	switch (phy_dev->speed) {
	case 1000:
		ctrl = GOOD_LINK_FORCE | SPEED_MODE_FORCE(2);
		rgmii_clk = MISCCTL_RGMII_1000;
		break;
	case 100:
		ctrl = GOOD_LINK_FORCE | SPEED_MODE_FORCE(1);
		rgmii_clk = MISCCTL_RGMII_100;
		break;
	default:
		ctrl = GOOD_LINK_FORCE | SPEED_MODE_FORCE(0);
		rgmii_clk = MISCCTL_RGMII_10;
		break;
	}

	if (phy_dev->duplex)
		ctrl |= FULL_DUPLEX_FORCE;

	writel(ctrl, priv->reg + NEM_GMAC_ANEG_CTRL_R);
	writel(rgmii_clk, priv->reg + NEM_DMA_MISC_CTL);

	/* Enable GMAC RX */
	enable = readl(priv->reg + NEM_GMAC_ENABLE_R);
	writel(enable | GMAC_RX_EN, priv->reg + NEM_GMAC_ENABLE_R);

	/* Enable DMA */
	writel(RXDMA_EN | TXDMA_EN, priv->reg + NEM_DMA_ENABLE);

	printf("NEMAC: %dMbps, %s duplex%s\n", phy_dev->speed,
	       (phy_dev->duplex) ? "full" : "half",
	       (phy_dev->port == PORT_FIBRE) ? ", fiber mode" : "");
}

static int
nemac_eth_init(struct eth_device *dev, bd_t *board_info)
{
	struct nemac_priv *priv = dev->priv;
	u32 tmp;
	int i;

	writel(~0, priv->reg + NEM_SWRESET_R);
	writel(0, priv->reg + NEM_SWRESET_R);

	writel(ACTIVE_GMAC0, priv->reg + NEM_ACTIVE_R);

	/* Disable and clear interrupts on top level */
	writel(0, priv->reg + NEM_INT_ENABLE_R);
	writel(~0, priv->reg + NEM_INT_STATUS_R);

	/* Intialize GMAC */
	tmp = readl(priv->reg + NEM_GMAC_ENABLE_R);
	tmp |= PORT_ENABLE | GMII_BYPASS_MODE | RGMII_MODE;
	writel(tmp, priv->reg + NEM_GMAC_ENABLE_R);

	writel((ENABLE_RUNT_FILTERING |
		ENABLE_PAUSE_FILTERING |
		ENABLE_UNICAST_FILTERING |
		PACKET_FILTERING_ENABLE),
	       priv->reg + NEM_GMAC_FILTER_CTRL_R);

	/* Setup DMA descriptors */

	/* Disable DMA */
	writel(0, priv->reg + NEM_DMA_ENABLE);

	/* RX queue */
	queue_init(&priv->rxq, RX_RING_SIZE, rxring,
		   readl(priv->reg + NEM_DMA_RXTAIL_PTR));
	writeq((u64)priv->rxq.ring, priv->reg + NEM_DMA_RXQ_ADDR);
	writel(priv->rxq.size / 1024, priv->reg + NEM_DMA_RXQ_SIZE);
	writel(priv->rxq.head, priv->reg + NEM_DMA_RXHEAD_PTR);
	writeq((u64)&priv->rxq.hw_tail, priv->reg + NEM_DMA_RXTAIL_PTR_ADDR);
	for (i = 0; i < PKTBUFSRX; ++i) {
		struct dma_desc *desc = &rxring[i];
		desc->ctrl = cpu_to_le32(DCTRL_INTR | DCTRL_SWAP);
		desc->xfer_len = PKTSIZE_ALIGN;
		desc->pdu_len = 0;
		desc->bufptr = cpu_to_le64((u64)NetRxPackets[i]);
		writel(queue_inc_head(&priv->rxq),
		       priv->reg + NEM_DMA_RXHEAD_PTR);
	}
	pr_queue("RXQ-INIT", &priv->rxq);

	/* TX queue */
	queue_init(&priv->txq, TX_RING_SIZE, txring,
		   readl(priv->reg + NEM_DMA_TXTAIL_PTR));
	writeq((u64)priv->txq.ring, priv->reg + NEM_DMA_TXQ_ADDR);
	writel(priv->txq.size / 1024, priv->reg + NEM_DMA_TXQ_SIZE);
	writel(priv->txq.head, priv->reg + NEM_DMA_TXHEAD_PTR);
	writeq((u64)&priv->txq.hw_tail, priv->reg + NEM_DMA_TXTAIL_PTR_ADDR);
	pr_queue("TXQ-INIT", &priv->txq);

	/* Enable DMA and tail-ptr writeback */
	tmp = readl(priv->reg + NEM_DMA_CTL);
	tmp |= DMACTL_EN | DMACTL_TX_TAIL_PTR_EN | DMACTL_RX_TAIL_PTR_EN;
	writel(tmp, priv->reg + NEM_DMA_CTL);

	/* Start up the PHY */
	if (phy_startup(priv->phy_dev) != 0) {
		printf("Failed to initialize PHY %s\n",
		       priv->phy_dev->dev->name);
		return -1;
	}

	nemac_link_up(priv, priv->phy_dev);

	/* If there's no link, fail */
	return priv->phy_dev->link ? 0 : -1;
}

static void
nemac_eth_halt(struct eth_device *dev)
{
	struct nemac_priv *priv = dev->priv;
	u32 tmp;

	writel(0, priv->reg + NEM_DMA_ENABLE);
	tmp = readl(priv->reg + NEM_DMA_CTL);
	tmp &= ~(DMACTL_EN | DMACTL_TX_TAIL_PTR_EN | DMACTL_RX_TAIL_PTR_EN);
	writel(tmp, priv->reg + NEM_DMA_CTL);

	/* Disable GMAC RX */
	tmp = readl(priv->reg + NEM_GMAC_ENABLE_R);
	tmp &= ~(PORT_ENABLE | GMAC_RX_EN);
	writel(tmp, priv->reg + NEM_GMAC_ENABLE_R);

	phy_shutdown(priv->phy_dev);
}

static int
nemac_eth_recv(struct eth_device *dev)
{
	struct nemac_priv *priv = dev->priv;
	struct dma_desc *desc;
	const u32 ok_flags = DCTRL_SOP | DCTRL_EOP;

	while ((desc = queue_get_tail(&priv->rxq)) != NULL) {
		int length = le16_to_cpu(desc->pdu_len);
		int status = cpu_to_le32(desc->ctrl);
		unsigned char *pkt = (unsigned char *)le64_to_cpu(desc->bufptr);

		queue_inc_tail(&priv->rxq);

		pr_desc("RX", desc);
		if (status & DCTRL_RX_ERR)
			printf("RX error %x\n", status);
		else if ((status & ok_flags) != ok_flags)
			printf("Bad status %x\n", status);
		else
			NetReceive(pkt, length);
		/* Re-initialize descriptor */
		desc->ctrl = cpu_to_le32(DCTRL_INTR | DCTRL_SWAP);
		desc->xfer_len = PKTSIZE_ALIGN;
		desc->pdu_len = 0;
		writel(queue_inc_head(&priv->rxq),
		       priv->reg + NEM_DMA_RXHEAD_PTR);
	}

	return 0;
}

static u32
check_dma_error(struct nemac_priv *priv)
{
	u32 e_status, l_status;

	e_status = readl(priv->reg + NEM_DMA_INTE_NOMASK);
	if (e_status) {
		if (e_status & INTE_ERR_MASK)
			printf("ERROR(DMA_INTE) %#x\n", e_status);
		writel(e_status, priv->reg + NEM_DMA_INTE_STATUS);
	}

	l_status = readl(priv->reg + NEM_DMA_INTL_NOMASK);
	if (l_status) {
		printf("ERROR(DMA_INTL) %#x\n", l_status);
		writel(l_status, priv->reg + NEM_DMA_INTL_STATUS);
	}

	return e_status | l_status;
}

static int
nemac_eth_send(struct eth_device *dev, void *packet, int length)
{
	struct nemac_priv *priv = dev->priv;
	struct dma_desc *desc;
	int tmo;

	desc = queue_get_head(&priv->txq);
	if (!desc) {
		puts("No TX descriptor!\n");
		return -1;
	}

	if (length < 60)
		length = 60;

	desc->ctrl = cpu_to_le32(DCTRL_INTR | DCTRL_SOP | DCTRL_EOP |
				 DCTRL_SWAP | DCTRL_TX_CRC);
	desc->xfer_len = cpu_to_le16(length);
	desc->pdu_len = desc->xfer_len;
	desc->bufptr = cpu_to_le64((u64)packet);
	pr_desc("TX", desc);
	writel(queue_inc_head(&priv->txq), priv->reg + NEM_DMA_TXHEAD_PTR);

	for (tmo = 0; queue_get_tail(&priv->txq) == NULL; ++tmo) {
		if (tmo >= 100000) {
			puts("TX timeout\n");
			return 0;
		}
		if (check_dma_error(priv))
			return 0;
	}
	queue_inc_tail(&priv->txq);

	return 0;
}

static int
nemac_write_hwaddr(struct eth_device *dev)
{
	struct nemac_priv *priv = dev->priv;
	u32 upper, lower;

	/* Set station address and unicast addr 1 */
	upper = ((dev->enetaddr[0] << 8) |
		 (dev->enetaddr[1] << 0));
	lower = ((dev->enetaddr[2] << 24) |
		 (dev->enetaddr[3] << 16) |
		 (dev->enetaddr[4] << 8)  |
		 (dev->enetaddr[5] << 0));
	writel(lower, priv->reg + NEM_GMAC_STA_ADDR_R);
	writel(upper, priv->reg + NEM_GMAC_STA_ADDR_UPPER_R);
	writel(lower, priv->reg + NEM_GMAC_UNICAST1_R);
	writel(upper, priv->reg + NEM_GMAC_UNICAST12_UPPER_R);
	return 0;
}

int
nemac_initialize(bd_t *bdi)
{
	struct eth_device *dev;
	struct mii_dev *bus;
	struct nemac_priv *priv;
	unsigned char ethaddr[6];

	bus = miiphy_get_dev_by_name(MDIO_DEV);
	if (bus == NULL) {
		puts("MDIO not available\n");
		return -1;
	}

	dev = malloc(sizeof(*dev));
	priv = malloc(sizeof(*priv));
	if (!dev || !priv) {
		puts("No memory\n");
		return -1;
	}

	memset(dev, 0, sizeof(*dev));
	memset(priv, 0, sizeof(*priv));

	sprintf(dev->name, "NEMAC");
	dev->priv = priv;
	dev->init = nemac_eth_init;
	dev->halt = nemac_eth_halt;
	dev->send = nemac_eth_send;
	dev->recv = nemac_eth_recv;
	dev->write_hwaddr = nemac_write_hwaddr;
	priv->dev = dev;
	priv->reg = (void __iomem *)NEMAC_BASE;
	debug("nemac base @ %p\n", priv->reg);

	if (eth_getenv_enetaddr("ethaddr", ethaddr))
		memcpy(dev->enetaddr, ethaddr, sizeof(ethaddr));

	eth_register(dev);

#if defined(CONFIG_AXXIA_56XX_EMU)
	/* Set bit[24] to mux RMII pins to NEMAC on emulation system */
	{
		void __iomem *ctrl = (void __iomem *)0x8080230018;
		writel((1 << 24) | readl(ctrl), ctrl);
	}
#endif

	priv->phy_dev = phy_connect(bus, CONFIG_AXXIA_PHY_ADDRESS, dev,
				    PHY_INTERFACE_MODE_RGMII);
	if (!priv->phy_dev) {
		free(priv);
		free(dev);
		return -1;
	}
	priv->bus = bus;

#if defined(CONFIG_AXXIA_56XX_EMU)
	/* Fixed setting for the emulation platform */
	priv->phy_dev->autoneg = AUTONEG_DISABLE;
	priv->phy_dev->speed = 10;
	priv->phy_dev->duplex = 0;
#endif
	phy_config(priv->phy_dev);

	return 0;
}
