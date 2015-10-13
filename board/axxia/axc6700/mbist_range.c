/*
 *  board/lsi/axxia-arm/mbist_range.c
 *
 *  Copyright (C) 2013 LSI (john.jacques@lsi.com)
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

/*************************************************************************
 * Take the list defined by address and length and sort them by address.
 * Then merge any adjacent or overlapping entries
 **************************************************************************/
void sortmerge(unsigned long addr[], unsigned long len[])
{
	unsigned long *addrp, *lenp;
	unsigned long *addrpt, *lenpt;
	unsigned long svaddr, svlen;
	unsigned long swapped;

	/* Sort the address list by address */
	for (swapped = 1; swapped; ) {
		/* Walk the list swapping entries until no swaps are needed */
		for (swapped = 0, addrp = addr, lenp = len;
			lenp[0] && lenp[1]; addrp++, lenp++) {
			if (addrp[0] > addrp[1]) {
				svaddr = addrp[0];
				svlen = lenp[0];
				addrp[0] = addrp[1];
				lenp[0] = lenp[1];
				addrp[1] = svaddr;
				lenp[1] = svlen;
				swapped = 1;
			}
		}
	}

	/* Combine any entries which are adjacent and/or overlap */
	for (addrp = addr, lenp = len; lenp[0]; addrp++, lenp++) {
		while (lenp[1] && (addrp[0] + lenp[0] >= addrp[1])) {
			/* This entry either touches or overlaps the
			 * next one. Combine them and slide all later
			 * entries down by one. The combination has
			 * to deal with the case where the next entry
			 * is entirely contained in this one */
			lenp[1] += (addrp[1] - addrp[0]);
			if (lenp[1] > lenp[0])
				lenp[0] = lenp[1];
			for (addrpt = addrp + 1, lenpt = lenp + 1; lenpt[0];
				addrpt++, lenpt++) {
				addrpt[0] = addrpt[1];
				lenpt[0] = lenpt[1];
			}
		}
	}
}

/***********************************************************************
* Take the list defined by in_addr and in_len and generate the inverse
* of the list in out_addr, out_len. The total memory size is defined by
* size
***********************************************************************/
void invert(unsigned long in_addr[], unsigned long in_len[],
	unsigned long out_addr[], unsigned long out_len[],
	unsigned long size) {
	unsigned long *addrp, *lenp;
	unsigned long *addrpt, *lenpt;

	/* First, make sure input is sorted and merged */
	sortmerge(in_addr, in_len);

	/* If the input doesn't start at 0, put in first entry
	 * for inverse starting at 0 */
	addrpt = out_addr;
	lenpt = out_len;
	if (in_addr[0]) {
		*addrpt++ = 0;
		*lenpt++ = in_addr[0];
	}

	/* Walk the rest of the list putting in inverted entries */
	for (addrp = in_addr, lenp = in_len; *lenp;
		addrp++, lenp++, addrpt++, lenpt++) {
		*addrpt = *addrp + *lenp;
		if (lenp[1]) {
			/* Not the last input entry - look at
			 * address of next one
			 * to get size of this output
			 */
			*lenpt = addrp[1] - *addrpt;
		} else {
			/* Last input entry - calculate length based on size */
			*lenpt = size - *addrpt;
			/* If this calculated length is 0, means that the input
			 * region ended at end of memory range
			 * Break out of for loop without incrementing
			 * output pointers
			 * to mark the current entry as the end marker
			 */
			if (!*lenpt)
				break;
		}
	}

	/* Mark the end of the list */
	*addrpt = *lenpt = 0;
}

/*********************************************************************
* mbist_range:
*
* Arguments:
* memsize -- Total DDR size in system. Must be power of 2
* dual_ddr -- True if dual smem configuration
* maskbits -- Number of ranks & bank bits. No more than 6.
* mbist_multiple -- Number that all mbist test outputs must be a
*	multiple of. This number will be rounded up to a power of 2.
*	0 Implies no multiple requirement.
* mbist_addr[], mbist_len[],
*	Input - user configuration set of addresses and lengths
*	Output - actual addresses & lengths to run in mbist
*	Length entry of 0 indicates end of list
*	On input, these are system memory addresses & lengths
*	On output, these are the values to program into DDR.
*	The dual smem conversion is handled when generating the outputs
* test_addr[],test_len[],
*	Output - system addresses which must be tested via SW
*	Length entry of 0 indicates end of list
* prot_addr[],prot_len[]
*	Output - system addresses which will not be touched at all
*	Length entry of 0 indicates end of list
*  Return values:
*  0 - OK
*  1 - dual_ddr is not set to 0 or 1
*  2 - maskbits is > 6
*  3 - memsize is not a power of 2
*  4 - some address or length is not a multiple of 4
*  5 - some address+length is greater than memory size
******************************************************************/
unsigned int mbist_range(
	unsigned long memsize,
	unsigned long dual_ddr,
	unsigned long maskbits,
	unsigned long mbist_multiple,
	unsigned long mbist_addr[],
	unsigned long mbist_len[],
	unsigned long test_addr[],
	unsigned long test_len[],
	unsigned long prot_addr[],
	unsigned long prot_len[])
{
	unsigned long i;
	unsigned long *addrp, *lenp;
	unsigned long *addrpt, *lenpt;
	unsigned long masklsb;
	unsigned long mask;

	/* Make sure dual_ddr is either 0 or 1 */
	if (dual_ddr > 1)
		return 1;

	/* maskbits should be no greater than 6 */
	if (maskbits > 6)
		return 2;

	/* Make sure memsize is a power of 2 */
	for (i = memsize; !(i&1); i >>= 1)
		;
	if (i != 1)
		return 3;

	/* Verify that all addresses and lengths are
	multiples of 4 (corresponds to 1K bytes) */
	for (addrp = mbist_addr, lenp = mbist_len; lenp[0]; addrp++, lenp++) {
		if ((addrp[0] & 3) || (lenp[0] & 3))
			return 4;
	}

	/* Verify that all addresses plus lengths are <= memory size */
	for (addrp = mbist_addr, lenp = mbist_len; lenp[0]; addrp++, lenp++) {
		if ((addrp[0] + lenp[0]) > memsize)
			return 5;
	}

	/* Round up mbist_multiple to a power of 2 */
	i = mbist_multiple | (mbist_multiple>>1);
	i |= (i>>2);
	i |= (i>>4);
	i |= (i>>8);
	i |= (i>>16);
	i += 1;
	if ((i >> 1) != mbist_multiple)
		mbist_multiple = i;
	if (!mbist_multiple)
		mbist_multiple = 1;

	/* Calculate the mask of which bits are updated by munging */
	mask = (memsize>>1);
	for (i = 1; i < maskbits; i++)
		mask |= (mask>>1);
	masklsb = (mask ^ (mask<<1)) & mask;

	/* Invert the mbist ranges into the protected ranges */
	invert(mbist_addr, mbist_len, prot_addr, prot_len, memsize);

	/* If there are no munged bits or no protected regions, just return */
	if (!maskbits || !prot_len[0]) {
		test_addr[0] = test_len[0] = 0;
		return 0;
	}

	/* Sort and merge the protected address list */
	sortmerge(prot_addr, prot_len);

	/* Copy and adjust the protected ranges. This will temporarily
	 * use the test_addr & test_len  arrays as storage. The adjustment
	 * is about clearing the bits which the munging might change
	 */
	for (addrp = prot_addr, lenp = prot_len, addrpt = test_addr,
		lenpt = test_len;
		*lenp; addrp++, lenp++, addrpt++, lenpt++) {
		if (*lenp & mask) {
			*addrpt = 0;
			*lenpt = ((memsize - 1) & ~mask) + 1;
		} else if ((*addrp & mask) == ((*addrp + *lenp) & mask)) {
			*addrpt = *addrp & ~mask;
			*lenpt = *lenp & ~mask;
		} else {
			/* Create 2 entries. First one covers the part of the
			 *  range that ends at the end of the masked address
			 */
			*addrpt = *addrp & ~mask;
			*lenpt++ = ((memsize - 1) & ~mask) + 1 - *addrpt++;

			/* Create the 2nd entry. Starts at beginning of
			 * masked address. Might be 0 length if this was
			 * at the end of all memory. Extra anding with
			 * ~memsize makes this entry the end of the list
			 */
			*addrpt = 0;
			*lenpt = (*addrp + *lenp) & ~mask & ~memsize;
		}
	}
	*addrpt = *lenpt = 0;

	/* Generate first set of mbist ranges. These are the ones with
	 * all the mask bits clear
	 */
	invert(test_addr, test_len, mbist_addr, mbist_len,
		((memsize - 1) & ~mask) + 1);

	/* Reduce all the mbist range lengths to make them multiples
	 *  of mbist_multiple - any entries which are now 0 length are removed
	 */
	for (addrp = addrpt = mbist_addr, lenp = lenpt = mbist_len;
		*lenp; addrp++, lenp++) {
		*addrpt = *addrp;
		if (*lenpt == (*lenpt & ~(mbist_multiple - 1))) {
			addrpt++;
			lenpt++;
		}
	}

	/*  The mbist entries all have the mask bits all clear. Duplicate
	 * with all other combinations of mask bits. The previous step
	 *  left addrpt & lenpt pointing at the end of the list. Keep walking
	 *  until source entry has all mask bits set
	 */
	for (addrp = mbist_addr, lenp = mbist_len;
		*lenp && ((*addrp & mask) != mask); addrp++, lenp++,
		addrpt++, lenpt++) {
		*addrpt = *addrp + masklsb;
		*lenpt = *lenp;
	}

	/* Mark end of list */
	*addrpt = *lenpt = 0;

	/* Sort and merge the mbist ranges */
	sortmerge(mbist_addr, mbist_len);

	/* Copy all the protected range and mbist ranges to the test list.
	 * This indicates all the addresses that software test does not
	 * need to cover.
	 * Start this list at the 2nd entry, since this leaves space for
	 * the final step
	 */
	for (addrpt = test_addr+1, lenpt = test_len+1,
		addrp = prot_addr, lenp = prot_len;
		*lenp; addrpt++, lenpt++, addrp++, lenp++) {
		*addrpt = *addrp;
		*lenpt = *lenp;
	}
	for (addrp = mbist_addr, lenp = mbist_len;
		*lenp; addrpt++, lenpt++, addrp++, lenp++) {
		*addrpt = *addrp;
		*lenpt = *lenp;
	}

	/* Mark end of list */
	*addrpt = *lenpt = 0;

	/* Generate actual list of SW tests required. This is the
	 * inverse of the list built till now
	 */
	invert(test_addr+1, test_len+1, test_addr, test_len, memsize);

	/* If we are in dual_ddr, cut all the mbist address
	 * and length in half */
	if (dual_ddr) {
		for (addrp = mbist_addr, lenp = mbist_len; *lenp;
			addrp++, lenp++) {
			*addrp >>= 1;
			*lenp >>= 1;
		}
	}

	/* All done */
	return 0;
}

void mbist_power2(unsigned long in_addr, unsigned long in_len,
	unsigned long mbist_addr[],
	unsigned long mbist_len[]) {
	unsigned int i;
	unsigned long *addrp;
	unsigned long *lenp;

	/* Determine the power of 2 lengths which add up to the in_len */
	for (i = 1, lenp = mbist_len; i; i <<= 1)
		if (in_len & i)
			*lenp++ = i;
	*lenp = 0;

	/* Fill in the mbist test list */
	for (addrp = mbist_addr, lenp = mbist_len,
		mbist_addr[0] = in_addr; *lenp; addrp++, lenp++) {
		addrp[1] = addrp[0] + lenp[0];
	}
	*addrp = 0;
}
