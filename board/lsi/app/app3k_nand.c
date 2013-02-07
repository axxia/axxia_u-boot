/*
 * app3k_nand.c
 *
 * NAND Flash memory access on APP3K based devices
 * 
 * Copyright (C) 2007 LSI Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <configs/app3k.h>

#if defined(CONFIG_COMMANDS) && defined(CONFIG_CMD_NAND) && !defined(CFG_NAND_LEGACY) && defined(LSI_ARCH_APP3K)

#include <common.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <asm/mach-types.h>

#if 0
#define APP3K_NAND_DEBUG
#endif

#ifdef APP3K_NAND_DEBUG
static int print_log = 0;
#endif

#define APP3K_NAND_CMD_START_ECC_READ   0x23
#define APP3K_NAND_CMD_CE_OFF           0xEE
#define NAND_CMD_RNDOUTSTART            0xE0

#define APP3K_EP501_ECC_NUM_BYTES       12

static struct nand_oobinfo app3k_nand_oob_layout = {
    .useecc = MTD_NANDECC_PLACEONLY,
	.eccbytes = APP3K_EP501_ECC_NUM_BYTES,
    .eccpos = {		   
		   52, 53, 54, 55, 56, 57, 
           58, 59, 60, 61, 62, 63},
	.oobfree = {{2, 50}}
};

/*
 *	hardware specific access to control-lines
 *
 */
static void app3k_nand_sel_chip(struct mtd_info *mtd, int chip)
{
#ifdef APP3K_NAND_DEBUG
    if(print_log) {
        printf(KERN_ERR "app3k_nand_sel_chip(): chipsel=%d\n", chip);
    }
#endif
}


/*
 *	hardware specific access to control-lines
 *
 */
static void app3k_nand_hwcontrol(struct mtd_info *mtd, int cmd)
{
	struct nand_chip *chip = NULL;

    if(!mtd) {
        printf(KERN_ERR "app3k_nand_hwcontrol(): ERROR: NULL mtd passed.\n");
        return;
    }

    chip = mtd->priv;

    if(!chip) {
        printf(KERN_ERR "app3k_nand_hwcontrol(): ERROR: NULL chip passed.\n");
        return;
    }
    
#ifdef APP3K_NAND_DEBUG
    if(cmd == NAND_CMD_SEQIN) {
        print_log = 1;
    }
    if(print_log && (cmd == NAND_CMD_SEQIN || cmd == NAND_CMD_READ0)) {
        printf(KERN_ERR "\n");
    }
#endif

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf(KERN_ERR "app3k_nand_hwcontrol(): cmd=0x%x\n", cmd);
#endif
    if((unsigned long)chip->IO_ADDR_W != CFG_NAND_BASE) {
        printf(KERN_ERR "app3k_nand_hwcontrol(): ERROR: Invalid NAND base: 0x%lx\n", 
            (unsigned long)chip->IO_ADDR_W);
        return;
    }
    writel(cmd, (chip->IO_ADDR_W + APP3K_NAND_CMD_REG));

#ifdef APP3K_NAND_DEBUG
    if(cmd == APP3K_NAND_CMD_CE_OFF || cmd == NAND_CMD_ERASE2)
        print_log = 0;
#endif
}

/*
 *	read device ready pin
 */
static int app3k_nand_device_ready(struct mtd_info *mtd)
{
    struct nand_chip *chip = mtd->priv;    
    int ready = 0;

    ready = readl(chip->IO_ADDR_R + APP3K_NAND_INTR_STATUS_REG);

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf(KERN_ERR "app3k_nand_device_ready(): ready: 0x%x\n", ready);
#endif

	return (ready & NAND_STATUS_TRUE_READY);
}

/**
 * app3k_nand_command - [DEFAULT] Send command to NAND large page device
 * @mtd:	MTD device structure
 * @command:	the command to be sent
 * @column:	the column address for this command, -1 if none
 * @page_addr:	the page address for this command, -1 if none
 *
 * Send command to NAND device. This is the version for the new large page
 * devices We dont have the separate regions as we have in the small page
 * devices.  We must emulate NAND_CMD_READOOB to keep the code compatible.
 */
static void app3k_nand_command(struct mtd_info *mtd, unsigned int command,
			    int column, int page_addr)
{
	register struct nand_chip *chip = mtd->priv;
    unsigned long index = 0;
    unsigned int status = 0;

    command &= 0xff;

#ifdef APP3K_NAND_DEBUG
    if (command == NAND_CMD_ERASE1) {
        print_log = 0;
    }
#endif

    /* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->oobblock;
		command = NAND_CMD_READ0;
	}

    /* return if unhandled command is issued */
    if(command != NAND_CMD_READ0 && command != NAND_CMD_SEQIN && command != NAND_CMD_ERASE1 && 
       command != NAND_CMD_STATUS && command != NAND_CMD_READID && command != NAND_CMD_RESET &&
       command != APP3K_NAND_CMD_START_ECC_READ && command != NAND_CMD_PAGEPROG &&
       command != NAND_CMD_ERASE2) {
        printf(KERN_ERR "app3k_nand_command(): WARN: Unhandled command 0x%x issued for page=0x%x, column=0x%x.\n",
            command, page_addr, column);
        return;
    }
    
	/* Command latch cycle */
	chip->hwcontrol(mtd, command);

	if (column != -1 || page_addr != -1) {
        /* column number */
        if (column != -1) {
            index = column & 0xfff;
        }
        /* page and block number */
        if (page_addr != -1) {
            index += ((page_addr & 0x7ffff) << 12);
        }

        /* write index reg */
        writel(index, chip->IO_ADDR_W + APP3K_NAND_INDEX_REG);

        /* write ext index reg */
        writel(0, chip->IO_ADDR_W + APP3K_NAND_EXT_INDEX_REG);
	}

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf(KERN_ERR "app3k_nand_command(): page=0x%x, col=0x%x, index=0x%lx\n",
            page_addr, column, index);
#endif

    /* for read command, send 0xe0 so data is populated */
	if(command == NAND_CMD_READ0) {
		chip->hwcontrol(mtd, NAND_CMD_RNDOUTSTART);
        /* wait until CHIP_BUSY goes low */
        do {
            udelay(chip->chip_delay);
            status = chip->dev_ready(mtd);
        } while(!status);
	} else if(command == NAND_CMD_STATUS) {
	    udelay(chip->chip_delay);
    }
}

/**
 * app3k_nand_read_buf - [DEFAULT] read chip data into buffer
 * @mtd:	MTD device structure
 * @buf:	buffer to store date
 * @len:	number of bytes to read
 *
 * Default read function for 8bit buswith
 */
static void app3k_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
    int i = 0;
	struct nand_chip *chip = mtd->priv;
    uint32_t *p = (uint32_t *)buf;
#ifdef APP3K_NAND_DEBUG
    if(print_log) {
        printf(KERN_ERR "READ Len: %d, Data:\n", len);
    }
#endif

    for (i = 0; i < (len >> 2); i++) {
        p[i] = readl(chip->IO_ADDR_R);
#ifdef APP3K_NAND_DEBUG
        if(print_log)
            printf("%08x-", p[i]);
#endif
    }

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf("\n");
#endif
}

/**
 * app3k_nand_write_buf - [DEFAULT] write buffer to chip
 * @mtd:	MTD device structure
 * @buf:	data buffer
 * @len:	number of bytes to write
 *
 * Default write function for 8bit buswith
 */
static void app3k_nand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
    int i = 0;
	struct nand_chip *chip = mtd->priv;
    uint32_t *p = (uint32_t *)buf;
#ifdef APP3K_NAND_DEBUG
    if(print_log) {
        printf(KERN_ERR "WRITE Len: %d, Data: ", len);
    }
#endif
	for (i = 0; i < (len >> 2); i++) {
		writel(p[i], chip->IO_ADDR_W);
#ifdef APP3K_NAND_DEBUG
        if(print_log)
            printf("%08x-", p[i]);
#endif
    }
#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf("\n");
#endif
}

/**
 * app3k_nand_verify_buf - [DEFAULT] Verify chip data against buffer
 * @mtd:	MTD device structure
 * @buf:	buffer containing the data to compare
 * @len:	number of bytes to compare
 *
 * Default verify function for 8bit buswith
 */
static int app3k_nand_verify_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;
    uint32_t *p = (uint32_t *)buf;

	for (i = 0; i < (len >> 2); i++) {
        udelay(chip->chip_delay);
		if (p[i] != readl((uint32_t *)chip->IO_ADDR_R))
			return -EFAULT;
    }
	return 0;
}

static int app3k_nand_read_status(struct mtd_info *mtd)
{    
    struct nand_chip *chip = mtd->priv;

    chip->hwcontrol(mtd, NAND_CMD_STATUS);

    return (readl(chip->IO_ADDR_R + APP3K_NAND_STATUS1_REG) & 0xff);
}


/**
 * app3k_nand_wait - [DEFAULT]  wait until the command is done
 * @mtd:	MTD device structure
 * @chip:	NAND chip structure
 *
 * Wait for command done. This applies to erase and program only
 * Erase can take up to 400ms and program up to 20ms according to
 * general NAND and SmartMedia specs
 */
static int app3k_nand_wait(struct mtd_info *mtd, struct nand_chip *chip, int state)
{
    int status = 0;
    loff_t offset = 0;

    while(1) {
        status = 0;
        udelay(chip->chip_delay);
        /* wait for PECC_BUSY to go down for reading or writing */
        if(state == FL_WRITING || state == FL_READING) {           
            status = readl(APP3K_AEI_LLP_CS_CTRL);
            
            /* bit 22 is nand_ecc_busy */
            if((status & 0x400000) == 0) {
                break;
            }
        }
        /* wait till PER/cache ready bit becomes ready */
        else if(state == FL_ERASING) {
            status = chip->dev_ready(mtd);
            if(status) {
                break;
            }
        } else {
            printf(KERN_ERR "WARN: NAND wait called in unknown state %d\n", state);
            break;
        }

#ifdef APP3K_NAND_DEBUG
        if(print_log)
            printf(KERN_ERR "app3k_nand_wait(): status=0x%x\n", status);
#endif
    }

    status = app3k_nand_read_status(mtd);
    if(status & NAND_STATUS_FAIL) {
        offset = (readl(chip->IO_ADDR_R + APP3K_NAND_INDEX_REG) >> 12) << 11;
        printf(KERN_ERR "app3k_nand_wait(): Action %d failed for Offset: 0x%llx, status 0x%x\n\n", 
            state, offset, status);
    }

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf(KERN_ERR "app3k_nand_wait(): return status=0x%x\n", status);
#endif
    
	return status;
}

void app3k_nand_ecc_hwctl(struct mtd_info *mtd, int mode)
{
    /* nothing to do to enable ECC */
}

int	app3k_nand_ecc_calculate(struct mtd_info *mtd,
					     const uint8_t *dat,
					     uint8_t *ecc_code)
{
    struct nand_chip *chip = mtd->priv;
    /* get the current operation by reading the cmd register */
    int cmd = readl(chip->IO_ADDR_R + APP3K_NAND_CMD_REG);
    int state = 0;

    /* start ECC calculation */
    if(cmd == NAND_CMD_RNDOUTSTART) {
        chip->cmdfunc(mtd, APP3K_NAND_CMD_START_ECC_READ, -1, -1);
        state = FL_READING;
    } else if(cmd == NAND_CMD_SEQIN) {
        chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
        state = FL_WRITING;
    }

    /* wait for PECC_BUSY to go down */
    return chip->waitfunc(mtd, chip, state);
}

int	app3k_nand_ecc_correct(struct mtd_info *mtd, uint8_t *dat,
					   uint8_t *read_ecc,
					   uint8_t *calc_ecc)
{
    /* nothing to do to correct ECC */
    return 0;
}

/**
 * nand_read_page_hwecc - hardware ecc based page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 *
 * Not for syndrome calculating ecc controllers which need a special oob layout
 */
int app3k_nand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				int page, uint8_t *buf, uint8_t *oobbuf)
{
	int i;
    unsigned long ecc_status = 0;

#ifdef APP3K_NAND_DEBUG
    if(print_log)
        printf(KERN_ERR "app3k_nand_read_page_hwecc(): Block=%d, page=%d\n", 
            page >> 6, page & 0x3f);
#endif

    /* read the page */
   	chip->read_buf(mtd, buf, mtd->oobblock);

    /* read oob data */
    chip->read_buf(mtd, oobbuf, mtd->oobsize);
    
    /* start ECC calculations */
	chip->calculate_ecc(mtd, NULL, NULL);

    /* Read the ECC Status and see if there were any errors */
    for(i = 0; i < (mtd->oobblock >> 9); i++) {
        ecc_status = readl(chip->IO_ADDR_R + APP3K_NAND_PECC_REG);
        if((ecc_status & 0x3000) == 1) {
            printf(KERN_ERR "Single ECC Error at page 0x%x column 0x%lx\n",
                page, ecc_status & 0xfff);
        } else if((ecc_status & 0x3000) == 2) {
            printf(KERN_ERR "Uncorrectable ECC Error at page 0x%x column 0x%lx\n",
                page, ecc_status & 0xfff);
        }
    }

    /* cmd to controller to turn off CE */
    chip->hwcontrol(mtd, APP3K_NAND_CMD_CE_OFF);
    
	return 0;
}

/**
 * app3k_nand_write_page_hwecc - hardware ecc based page write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
 */
static void app3k_nand_write_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				  const uint8_t *oobbuf)
{   
#ifdef APP3K_NAND_DEBUG
    int page = 0;

    /* get the current page number */
    page = readl(chip->IO_ADDR_R + APP3K_NAND_INDEX_REG) >> 12;
    printf(KERN_ERR "app3k_nand_write_page_hwecc(): Block=%d, page=%d\n", 
        page >> 6, page & 0x3f);
#endif

    /* write the page data */
    chip->write_buf(mtd, chip->data_poi, mtd->oobblock);

    /* 
     * Write the oob data. Last 12 bytes are used by HW ECC. Do not touch them.
     */
    chip->write_buf(mtd, oobbuf, mtd->oobsize - APP3K_EP501_ECC_NUM_BYTES);
}

/**
 * app3k_nand_write_page - [REPLACEABLE] write one page
 * @mtd:	MTD device structure
 * @chip:	NAND chip descriptor
 * @buf:	the data to write
 * @page:	page number to write
 * @cached:	cached programming
 * @raw:	use _raw version of write_page
 */
int app3k_nand_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			   int page, const uint8_t *oobbuf, struct nand_oobinfo *oobsel, int cached)
{
	int status;
#ifdef APP3K_NAND_DEBUG
    printf(KERN_ERR "app3k_nand_write_page(): Block=%d, page=%d\n", 
        page >> 6, page & 0x3f);
#endif

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x00, page);

    /* write the page and oob data */
    app3k_nand_write_page_hwecc(mtd, chip, oobbuf);

    /* calculate ECC */
	status = chip->calculate_ecc(mtd, NULL, NULL);

    /* cmd to controller to turn off CE */
    chip->hwcontrol(mtd, APP3K_NAND_CMD_CE_OFF);

    /*
	 * See if operation failed and additional status checks are
	 * available
	 */
	if (status & NAND_STATUS_FAIL) {
        printf(KERN_ERR "ERROR: Page write failed for page 0x%x\n", page);
        return -EIO;
    }    

#ifdef CONFIG_MTD_NAND_VERIFY_WRITE
	/* Send command to read back the data */
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	if (chip->verify_buf(mtd, chip->data_poi, mtd->oobblock))
		return -EIO;
#endif
	return 0;
}


/**
 * app3k_nand_read_oob_std - [REPLACABLE] the most common OOB data read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to read
 * @sndcmd:	flag whether to issue read command or not
 */
int app3k_nand_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
			     int page, int col, uint8_t *buf)
{
    unsigned long ecc_status = 0;
    int i = 0;
#ifdef APP3K_NAND_DEBUG
    printf(KERN_ERR "app3k_nand_read_oob(): block=%d, page=%d, col=0x%x\n", 
        page >> 6, page & 0x3f, col);
#endif


    /* send command to read oob */    
	chip->cmdfunc(mtd, NAND_CMD_READOOB, col, page);
    
	/* read oob data */
    chip->read_buf(mtd, buf, mtd->oobsize - col);
    
    /* start ECC calculations */
	chip->calculate_ecc(mtd, NULL, NULL);

    /* Read the ECC Status and see if there were any errors */
    for(i = 0; i < (mtd->oobblock >> 9); i++) {
        ecc_status = readl(chip->IO_ADDR_R + APP3K_NAND_PECC_REG);
        if((ecc_status & 0x3000) == 1) {
            printf(KERN_ERR "Single ECC Error at page 0x%x column 0x%lx\n",
                page, ecc_status & 0xfff);
        } else if((ecc_status & 0x3000) == 2) {
            printf(KERN_ERR "Uncorrectable ECC Error at page 0x%x column 0x%lx\n",
                page, ecc_status & 0xfff);
        }
    }

    /* cmd to controller to turn off CE */
    chip->hwcontrol(mtd, APP3K_NAND_CMD_CE_OFF);
    
	return 0;
}

/**
 * app3k_nand_write_oob_std - [REPLACABLE] the most common OOB data write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to write
 */
int app3k_nand_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
			      int page, int col, const uint8_t *buf)
{
#ifdef APP3K_NAND_DEBUG
    printf(KERN_ERR "app3k_nand_write_oob(): block=%d, page=%d, col=0x%x\n", 
        page >> 6, page & 0x3f, col);
#endif

    /* start OOB write */
	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->oobblock + col, page);

    /* 
     * Write the oob data. Last 12 bytes are used by HW ECC. Do not touch them.
     */
    chip->write_buf(mtd, buf, mtd->oobsize - APP3K_EP501_ECC_NUM_BYTES);

    /* calculate ECC */
	chip->calculate_ecc(mtd, NULL, NULL);

    /* cmd to controller to turn off CE */
    chip->hwcontrol(mtd, APP3K_NAND_CMD_CE_OFF);

	return (chip->dev_ready(mtd) & NAND_STATUS_FAIL) ? -EIO : 0;
}

/*
 * NAND initialization routine
 */
void board_nand_init(struct nand_chip *nand)
{
    unsigned long data = 0;

	/* init chip callbacks */
    nand->write_buf = app3k_nand_write_buf;
    nand->read_buf = app3k_nand_read_buf;
    nand->verify_buf = app3k_nand_verify_buf;    
	nand->hwcontrol = app3k_nand_hwcontrol;
	nand->dev_ready = app3k_nand_device_ready;
    nand->cmdfunc = app3k_nand_command;
    nand->waitfunc = app3k_nand_wait;
    nand->select_chip = app3k_nand_sel_chip;
	nand->chip_delay = 30;    
    nand->options = NAND_USE_FLASH_BBT;

    /* initialize ECC */
    nand->eccmode = NAND_ECC_HW12_2048;
    nand->enable_hwecc = app3k_nand_ecc_hwctl;
    nand->calculate_ecc = app3k_nand_ecc_calculate;
    nand->correct_data = app3k_nand_ecc_correct;
    nand->autooob = &app3k_nand_oob_layout;

    /* reset nand controller */    
    data = readl(APP3K_AEI_LLP_CS_CTRL);
    data |= 0x200000;
    writel(data, APP3K_AEI_LLP_CS_CTRL);
    data &= ~(0x200000);
    writel(data, APP3K_AEI_LLP_CS_CTRL);
    
    /* clear any existing ECC status */
    writel(0x0, nand->IO_ADDR_W + APP3K_NAND_INTR_STATUS_REG);
    /* enable ECC */
    writel(0x0, nand->IO_ADDR_W + APP3K_NAND_INTR_EN_REG);

    /* setup timing ctrl 0 reg */
    data = 0x05;            /* setup time for CLE, CE# and ALE to command */
    data |= (0x0c << 8);    /* write pulse width */
    data |= (0x0c << 16);   /* read pulse width */
    data |= (0x03 << 24);   /* CLE, CE# and ALE hold time relative to WE# rising edge */
    writel(data, nand->IO_ADDR_W + APP3K_NAND_TIMING1_REG);

    /* setup timing ctrl 1 reg */
    data = 0x3;             /* setup time for CLE, CE# and ALE to command */
    data |= (0x03 << 8);    /* write pulse width */
    data |= (0x07 << 16);   /* read pulse width */
    data |= (0x1e << 24);   /* CLE, CE# and ALE hold time relative to WE# rising edge */
    writel(data, nand->IO_ADDR_W + APP3K_NAND_TIMING2_REG);    
}

#endif /* #if (CONFIG_COMMANDS & CFG_CMD_NAND) && !defined(CFG_NAND_LEGACY) && defined(LSI_ARCH_APP3K) */
