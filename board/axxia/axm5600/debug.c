/*
* debug.c
*
* Copyright (C) 2013 LSI Corporation
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*/

#include <common.h>

/*
------------------------------------------------------------------------------
Short Descriptors

------------------------------------------------------------------------------
------------------------------------------------------------------------------
From the ARM ARM table describing the PAR, and other places.
------------------------------------------------------------------------------
------------------------------------------------------------------------------

=============================
== Inner Memory Attributes ==
=============================

0b111 Write-Back, no Write-Allocate.
0b110 Write-Through.
0b101 Write-Back, Write-Allocate.
0b011 Device.
0b001 Strongly-ordered.
0b000 Non-cacheable.

=============================
== Outer Memory Attributes ==
=============================

0b11 Write-Back, no Write-Allocate.
0b10 Write-Through, no Write-Allocate.
0b01 Write-Back, Write-Allocate.
0b00 Non-cacheable.
*/

struct par32_reg {
	unsigned long    f  :1;
	unsigned long   ss  :1;
	unsigned long outer :2;
	unsigned long inner :3;
	unsigned long    sh :1;
	unsigned long   imp :1;
	unsigned long    ns :1;
	unsigned long   nos :1;
	unsigned long  lpae :1;
	unsigned long    pa :20;
};

static void
short_descriptor(void *virtual, struct par32_reg *par)
{
	unsigned long long pa;

	if (1 == par->f) {
		/* Fault! */
		printf("Fault: 0x%02lx\n", (*((unsigned long *)par) & 0x7e) >> 1);

		return;
	}

	if (0 != par->ss) {
		/* Supersection. */
		pa = (unsigned long long)(par->pa & 0xff0) << 28 |
			(unsigned long long)(par->pa & 0xff000) << 12;
		/* Add the bottom 24 bits from the virtual address. */
		pa |= (unsigned long long)((unsigned long)virtual & 0xffffff);
	} else {
		/* NOT a Supersection */
		pa = (unsigned long long)(par->pa) << 12;
		/* Add the bottom 12 bits from the virtual address. */
		pa |= (unsigned long long)((unsigned long)virtual & 0xfff);
	}

	printf("Virtual: 0x%p  Physical: 0x%016llx\n"
	       "    Inner: 0x%x Outer: 0x%x sh/nos: %d/%d\n"
	       "Inner: ",
	       virtual, pa, par->inner, par->outer, par->sh, par->nos);

	switch (par->inner) {
	case 7:
		printf("Write-Back, no Write-Allocate");
		break;
	case 6:
		printf("Write-Through");
		break;
	case 5:
		printf("Write-Back, Write-Allocate");
		break;
	case 3:
		printf("Device");
		break;
	case 1:
		printf("Strongly-ordered");
		break;
	case 0:
		printf("Non-cacheable");
		break;
	default:
		printf("Undefined");
		break;
	}

	printf(" Outer: ");

	switch (par->outer) {
	case 3:
		printf("Write-Back, no Write-Allocate\n");
		break;
	case 2:
		printf("Write-Through, no Write-Allocate\n");
		break;
	case 1:
		printf("Write-Back, Write-Allocate\n");
		break;
	case 0:
		printf("Non-cacheable\n");
	default:
		break;
	}

	printf("Sharable: %d Not Outer Sharable: %d (only valid if Sharable)\n",
	       par->sh, par->nos);

	return;
}

/*
------------------------------------------------------------------------------
Long Descriptors

------------------------------------------------------------------------------
------------------------------------------------------------------------------
From the ARM ARM table describing MAIR attribute fields and other places...
------------------------------------------------------------------------------
------------------------------------------------------------------------------

===========================
==== Attr[7:4] Meaning ====
===========================

== 0000 ==

Strongly-ordered or Device memory, see encoding of Attr[3:0].

== 00RW, RW not 00 ==

It is IMPLEMENTATION DEFINED whether the encoding is:
* UNPREDICTABLE
* Normal memory, Outer Write-Through (b) Transient.

== 0100 ==

Normal memory, Outer (a) Non-cacheable.

== 01RW, RW not 00 ==

It is IMPLEMENTATION DEFINED whether the encoding is:
* UNPREDICTABLE
* Normal memory, Outer Write-Back (b) Transient.

== 10RW ==

Normal memory, Outer (a) Write-Through Cacheable (b), Non-transient (c).

== 11RW ==

Normal memory, Outer (a) Write-Back Cacheable (b), Non-transient (c).

===========================
==== Attr[3:0] Meaning ====
===========================

== 0000  AND Attr[7:4] is ZERO ==

Strongly-ordered memory

== 0000  AND Attr[7:4] is NOT ZERO ==

UNPREDICTABLE

== 00RW, RW not 00 AND Attr[7:4] is ZERO ==

UNPREDICTABLE

== 00RW, RW not 00 AND Attr[7:4] is NOT ZERO ==

It is IMPLEMENTATION DEFINED whether the encoding is:
* UNPREDICTABLE
* Normal memory, Inner Write-Through (b) Transient

== 0100 AND Attr[7:4] is ZERO ==

Device memory

== 0100 AND Attr[7:4] is NOT ZERO ==

Normal memory, Inner Non-cacheable.

== 01RW, RW not 00 AND Attr[7:4] is ZERO ==

UNPREDICTABLE

== 01RW, RW not 00 AND Attr[7:4] is NOT ZERO ==

It is IMPLEMENTATION DEFINED whether the encoding is:
* UNPREDICTABLE
* Normal memory, Inner Write-Back (b) Transient

== 10RW AND Attr[7:4] is ZERO ==

UNPREDICTABLE

== 10RW AND Attr[7:4] is NOT ZERO ==

Normal memory, Inner Write-Through Cacheable (b), Non-transient (c).

== 11RW AND Attr[7:4] is ZERO ==

UNPREDICTABLE

== 11RW AND Attr[7:4] is NOT ZERO ==

Normal memory, Inner Write-Back Cacheable (b), Non-transient (c).

(a) See encoding of Attrm[3:0] for Inner cacheability policies.
(b) R defines the Outer Read-Allocate policy, and W defines the Outer
Write-Allocate policy.  0 => do not allocate, 1 => allocate.
(c) Non-transient if the implementation includes support for the
Transient attribute.

=====================
==== Sharability ====
=====================

00    Not Sharable
01    UNPREDICTABLE
10    Outer Sharable
11    Inner Sharable
*/

struct par64_reg {
	unsigned long long    f :1;
	unsigned long long      :6;
	unsigned long long   sh :2;
	unsigned long long   ns :1;
	unsigned long long  imp :1;
	unsigned long long lpae :1;
	unsigned long long   pa :28;
	unsigned long long      :16;
	unsigned long long attr :8;
};

static void
print_id_warning(int attr)
{
	printf("FIXME: Implementation Defined!  Attributes are 0x%x\n", attr);

	return;
}

static void
print_rw(int rw)
{
	printf("\t%s %s\n",
	       (0 == (rw & 2)) ?
	       "No Read Allocate" : "Read Allocate",
	       (0 == (rw & 1)) ?
	       "No Write Allocate" : "Write Allocate");

	return;
}

static void
long_descriptor(void *virtual, struct par64_reg *par)
{
	unsigned long long pa;

	if (1 == par->f) {
		/* Fault! */
		printf("Fault: 0x%02llx\n",
		       (*((unsigned long long *)par) & 0x7e) >> 1);

		return;
	}

	pa = ((unsigned long long)(par->pa) << 12) |
		(unsigned long long)((unsigned long)virtual & 0xfff);

	printf("Virtual: 0x%p  Physical: 0x%016llx\n"
	       "    attr: 0x%x sh: 0x%x\n",
	       virtual, pa, par->attr, par->sh);

	switch ((par->attr & 0xf0) >> 4) {
	case 0:
		switch (par->attr & 0xf) {
		case 0:
			printf("Strongly Ordered\n");
			break;
		case 4:
			printf("Device Memory\n");
			break;
		default:
			printf("Unpredictable\n");
			break;
		}
		break;
	case 1:
	case 2:
	case 3:
		print_id_warning(par->attr);
		break;
	case 4:
		printf("Normal Memory\n");
		printf("Outer: Non-Cacheable\n");

		switch (par->attr & 0xf) {
		case 0:
			printf("Inner: Unpredictable\n");
			break;
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
			print_id_warning(par->attr);
			break;
		case 4:
			printf("Inner: Non-Cachable\n");
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			printf("Inner: Write-Through Cacheable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			printf("Inner: Write-Back Cacheable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		default:
			printf("Unpredictable\n");
			break;
		}
	case 8:
	case 9:
	case 10:
	case 11:
		printf("Normal Memory\n");
		printf("Outer: Write-Through Cachable, Non-Transient\n");
		print_rw(((par->attr & 0xf0) >> 4) & 3);

		switch (par->attr & 0xf) {
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
			print_id_warning(par->attr);
			break;
		case 4:
			printf("Inner: Non-Cachable\n");
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			printf("Inner: Write-Through Cachable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			printf("Inner: Write-Back Cachable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		default:
			printf("Unpredictable\n");
			break;
		}
		break;
	case 12:
	case 13:
	case 14:
	case 15:
		printf("Normal Memory\n");
		printf("Outer: Write-Back Cachable, Non-Transient\n");
		print_rw(((par->attr & 0xf0) >> 4) & 3);

		switch (par->attr & 0xf) {
		case 1:
		case 2:
		case 3:
		case 5:
		case 6:
		case 7:
			print_id_warning(par->attr);
			break;
		case 4:
			printf("Inner: Non-Cachable\n");
			break;
		case 8:
		case 9:
		case 10:
		case 11:
			printf("Inner: Write-Through Cachable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			printf("Inner: Write-Back Cachable, Non-Transient\n");
			print_rw(par->attr & 3);
			break;
		default:
			printf("Unpredictable\n");
			break;
		}
		break;
		break;
	default:
		print_id_warning(par->attr);
		break;
	}

	printf("Shareability: ");

	switch (par->sh) {
	case 0:
		printf("Not Shareable\n");
		break;
	case 2:
		printf("Outer Shareable\n");
		break;
	case 3:
		printf("Inner Shareable\n");
		break;
	default:
		printf("Unpredictable\n");
		break;}

	return;
}

/*
------------------------------------------------------------------------------
display_va_attr

*/

void
display_va_attr(void *virtual)
{
	unsigned long long physical;
	unsigned long pal;
	unsigned long pah;

	asm volatile ("mcr p15, 0, %0, c7, c8, 0" : : "r" (virtual));
	asm volatile ("mrrc p15, 0, %0, %1, c7" : "=r" (pal), "=r" (pah));
	physical = ((unsigned long long)pah << 32) | (unsigned long long)pal;

	if (0 == (pal & (1 << 11)))
		short_descriptor(virtual, (struct par32_reg *)&pal);
	else
		long_descriptor(virtual, (struct par64_reg *)&physical);

	return;
}
