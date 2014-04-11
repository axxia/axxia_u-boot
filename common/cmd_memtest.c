/*
 * common/cmd_memtest.c
 *
 * Released under version 2 of the Gnu Public License.
 * By Chris Brady, cbrady@sgi.com
 * ----------------------------------------------------
 * MemTest86+ V3.00 Specific code (GPL V2.0)
 * By Samuel DEMEULEMEESTER, sdemeule@memtest.org
 * http://www.canardpc.com - http://www.memtest.org
 */

#include <common.h>
#include <command.h>
#include <watchdog.h>

#define hprint(...)
#define cprint(...)
#define dprint(...)

#define SPINSZ    0x2000000
#define MOD_SZ    20

struct tseq {
	short cache;
	short pat;
	short iter;
	short errors;
	const char *msg;
};

static const struct tseq tseq[] = {
	{1,  5,   4, 0, "[Address test, walking ones]          "},
	{1,  6,   4, 0, "[Address test, own address]           "},
	{1,  0,   4, 0, "[Moving inversions, ones & zeros]     "},
	{1,  1,   2, 0, "[Moving inversions, 8 bit pattern]    "},
	{1, 10,  50, 0, "[Moving inversions, random pattern]   "},
	/*   {1,  7,  80, 0, "[Block move, 80 moves]                "}, */
	{1,  2,   2, 0, "[Moving inversions, 32 bit pattern]   "},
	{1,  9,  30, 0, "[Random number sequence]              "},
	{1, 11,   6, 0, "[Modulo 20, Random pattern]           "},
	/*   {1,  8,   1, 0, "[Bit fade test, 90 min, 2 patterns]   "}, */
};

#define NTESTS (sizeof(tseq)/sizeof(tseq[0]))

static ulong *map_start, *map_end;
static volatile ulong *p;
static ulong errors;
static int abort_memtest;

static unsigned int SEED_X = 521288629;
static unsigned int SEED_Y = 362436069;

unsigned int
rand(void)
{
	static unsigned int a = 18000, b = 30903;

	SEED_X = a*(SEED_X&65535) + (SEED_X>>16);
	SEED_Y = b*(SEED_Y&65535) + (SEED_Y>>16);

	return ((SEED_X<<16) + (SEED_Y&65535));
}


static void
rand_seed( unsigned int seed1, unsigned int seed2 )
{
	if (seed1) SEED_X = seed1;   /* use default seeds if parameter is 0 */
	if (seed2) SEED_Y = seed2;
}

static void
sleep(unsigned sec)
{
	ulong start = get_timer(0);
   
	sec *= CONFIG_SYS_HZ;

	while (get_timer(start) < sec) {
		if (ctrlc()) {
			abort_memtest = 1;
			return;
		}
		udelay(100);
	}
}
#define sleep(_x) do {				\
		sleep(_x);			\
		if (abort_memtest) return;	\
	} while(0)

#undef error
static void
error(ulong *adr, ulong good, ulong bad)
{
	ulong xor = good ^ bad;
   
	printf("DATA ERROR @ %p\tgood %08lx\tbad %08lx\tdiff %08lx\n",
	       adr, good, bad, xor);
	errors++;
}

static void
ad_err1(ulong *adr, ulong *mask, ulong bad, ulong good)
{
	ulong xor = good ^ bad;

	printf("ADDRESS LINE ERROR @ %p\tline mask %08lx\tgood %08lx\tbad %08lx\tdiff %08lx\n",
	       adr, (ulong)mask, good, bad, xor);
	errors++;
}

static void
ad_err2(ulong *adr, ulong bad)
{
	printf("OWN ADDRESS ERROR @ %p\tbad %08lx\tdiff %08lx\n",
	       adr, bad, ((ulong)adr) ^ bad);
	errors++;
}

static void
do_tick(void)
{
	/*  WATCHDOG_RESET();  */
	putc('*');

	if (ctrlc()) {
		abort_memtest = 1;
		return;
	}
}
#define do_tick() do {				\
		do_tick();			\
		if (abort_memtest) return;	\
	} while(0)

#undef roundup
static inline
ulong roundup(ulong value, ulong mask)
{
	return (value + mask) & ~mask;
}

/*
 * Memory address test, walking ones
 */
static void
addr_tst1(void)
{
	int i, j, k;
	volatile ulong *pt;
	volatile ulong *end;
	ulong bad, mask, bank;
	ulong p1;

	/* Test the global address bits */
	for (p1=0, j=0; j<2; j++) {
		hprint(LINE_PAT, COL_PAT, p1);

		/* Set pattern in our lowest multiple of 0x20000 */
		p = (ulong *)roundup((ulong)map_start, 0x1ffff);
		*p = p1;

		/* Now write pattern compliment */
		p1 = ~p1;
		end = map_end;
		for (i=0; i<100; i++) {
			mask = 4;
			do {
				pt = (ulong *)((ulong)p | mask);
				if ((uintptr_t)pt == (uintptr_t)p) {
					mask = mask << 1;
					continue;
				}
				if ((uintptr_t)pt >= (uintptr_t)end) {
					break;
				}
				*pt = p1;
				if ((uintptr_t)(bad = *p) != (uintptr_t)~p1) {
					ad_err1((ulong *)p, (ulong *)mask,
					        bad, ~p1);
					i = 1000;
				}
				mask = mask << 1;
			} while(mask);
		}
		do_tick();
	}

	/* Now check the address bits in each bank */
	/* If we have more than 8mb of memory then the bank size must be */
	/* bigger than 256k.  If so use 1mb for the bank size. */
	bank = 0x100000;

	for (p1=0, k=0; k<2; k++) {
		hprint(LINE_PAT, COL_PAT, p1);

		p = map_start;
		/* Force start address to be a multiple of 256k */
		p = (ulong *)roundup((ulong)p, bank - 1);
		end = map_end;
		while ((uintptr_t)p < (uintptr_t)end) {
			*p = p1;

			p1 = ~p1;
			for (i=0; i<200; i++) {
				mask = 4;
				do {
					pt = (ulong *)
						((ulong)p | mask);
					if ((uintptr_t)pt == (uintptr_t)p) {
						mask = mask << 1;
						continue;
					}
					if ((uintptr_t)pt >= (uintptr_t)end) {
						break;
					}
					*pt = p1;
					if ((uintptr_t)(bad = *p) != (uintptr_t)~p1) {
						ad_err1((ulong *)p,
							(ulong *)mask,
							bad,~p1);
						i = 200;
					}
					mask = mask << 1;
				} while(mask);
			}
			if ((uintptr_t)(p + bank/4) > (uintptr_t)p) {
				p += bank/4;
			} else {
				p = end;
			}
			p1 = ~p1;
		}
		
		do_tick();
		p1 = ~p1;
	}
}

/*
 * Memory address test, own address
 */

static void
addr_tst2(void)
{
	int done;
	volatile ulong *pe;
	volatile ulong *end, *start;
	ulong bad;

	cprint(LINE_PAT, COL_PAT, "        ");

	/* Write each address with it's own address */
	start = map_start;
	end = map_end;
	pe = (ulong *)start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}

		for (; p < pe; p++) {
			*p = (ulong)p;
		}

		do_tick();
	} while (!done);

	/* Each address should have its own address */
	start = map_start;
	end = map_end;
	pe = (ulong *)start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe ) {
			break;
		}

		for (; p < pe; p++) {
			if((bad = *p) != (ulong)p) {
				ad_err2((ulong*)p, bad);
			}
		}

		do_tick();
	} while (!done);
}

/*
 * Test all of memory using a "half moving inversions" algorithm using random
 * numbers and their complment as the data pattern. Since we are not able to
 * produce random numbers in reverse order testing is only done in the forward
 * direction.
 */

static void
movinvr(void)
{
	int i, done, seed1, seed2;
	volatile ulong *pe;
	volatile ulong *start,*end;
	ulong num;
	uintptr_t seg_start;
	ulong bad;

	/* Initialize memory with initial sequence of random numbers.  */
	seed1 = 521288629 + get_ticks();
	seed2 = 362436069 + get_ticks();

	/* Display the current seed */
	hprint(LINE_PAT, COL_PAT, seed1);
	rand_seed(seed1, seed2);
	start = map_start;
	end = map_end;
	pe = start;
	p = start;
	seg_start = (uintptr_t)p;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if (seg_start == (uintptr_t)pe) {
			break;
		}

		for (; p < pe; p++) {
			*p = rand();
		}

		do_tick();
	} while (!done);

	/* Do moving inversions test. Check for initial pattern and then
	 * write the complement for each memory location. Test from bottom
	 * up and then from the top down.  */
	for (i=0; i<2; i++) {
		rand_seed(seed1, seed2);
		start = map_start;
		end = map_end;
		pe = start;
		p = start;
		seg_start = (uintptr_t)p;
		done = 0;
		do {
			/* Check for overflow */
			if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
				pe += SPINSZ;
			} else {
				pe = end;
			}
			if ((uintptr_t)pe >= (uintptr_t)end) {
				pe = end;
				done++;
			}
			if (seg_start == (uintptr_t)pe) {
				break;
			}

			for (; p < pe; p++) {
				num = rand();
				if (i) {
					num = ~num;
				}
				if ((bad=*p) != num) {
					error((ulong*)p, num, bad);
				}
				*p = ~num;
			}

			do_tick();
		} while (!done);
	}
}

/*
 * Test all of memory using a "moving inversions" algorithm using the
 * pattern in p1 and it's complement in p2.
 */

static void
movinv1(int iter, ulong p1, ulong p2)
{
	int i, done;
	volatile ulong *pe;
	volatile ulong *start,*end;
	ulong bad;

	/* Display the current pattern */
	hprint(LINE_PAT, COL_PAT, p1);

	/* Initialize memory with the initial pattern.  */
	start = map_start;
	end = map_end;
	pe = start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe)
			pe += SPINSZ;
		else
			pe = end;

		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}

		if ((uintptr_t)p == (uintptr_t)pe)
			break;

		for (; p < pe; p++) {
			*p = p1;
		}

		do_tick();
	} while (!done);

	/* Do moving inversions test. Check for initial pattern and then
	 * write the complement for each memory location. Test from bottom
	 * up and then from the top down.  */
	for (i=0; i<iter; i++) {
		start = map_start;
		end = map_end;
		pe = start;
		p = start;
		done = 0;
		do {
			/* Check for overflow */
			if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe)
				pe += SPINSZ;
			else
				pe = end;

			if ((uintptr_t)pe >= (uintptr_t)end) {
				pe = end;
				done++;
			}

			if ((uintptr_t)p == (uintptr_t)pe)
				break;

			for (; p < pe; p++) {
				if ((bad=*p) != p1)
					error((ulong*)p, p1, bad);

				*p = p2;
			}

			do_tick();
		} while (!done);

		start = map_start;
		end = map_end;
		pe = end -1;
		p = end -1;
		done = 0;
		do {
			/* Check for underflow */
			if ((uintptr_t)(pe - SPINSZ) < (uintptr_t)pe)
				pe -= SPINSZ;
			else
				pe = start;

			if ((uintptr_t)pe <= (uintptr_t)start) {
				pe = start;
				done++;
			}

			if ((uintptr_t)p == (uintptr_t)pe)
				break;

			do {
				if ((bad=*p) != p2)
					error((ulong*)p, p2, bad);

				*p = p1;
			} while (p-- > pe);

			do_tick();
		} while (!done);
	}
}

static void
movinv32(int iter, ulong p1, ulong lb, ulong hb, int sval, int off)
{
	int i, k=0, done;
	volatile ulong *pe;
	volatile ulong *start, *end;
	ulong pat = 0;
	ulong bad;
	ulong p3 = sval << 31;

	/* Display the current pattern */
	hprint(LINE_PAT, COL_PAT, p1);

	/* Initialize memory with the initial pattern.  */
	start = map_start;
	end = map_end;
	pe = start;
	p = start;
	done = 0;
	k = off;
	pat = p1;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}
		/* Do a SPINSZ section of memory */

		while (p < pe) {
			*p = pat;
			if (++k >= 32) {
				pat = lb;
				k = 0;
			} else {
				pat = pat << 1;
				pat |= sval;
			}
			p++;
		}

		do_tick();
	} while (!done);

	/* Do moving inversions test. Check for initial pattern and then
	 * write the complement for each memory location. Test from bottom
	 * up and then from the top down.  */
	for (i=0; i<iter; i++) {
		start = map_start;
		end = map_end;
		pe = start;
		p = start;
		done = 0;
		k = off;
		pat = p1;
		do {
			/* Check for overflow */
			if ((uintptr_t)(pe + SPINSZ) > (uintptr_t)pe) {
				pe += SPINSZ;
			} else {
				pe = end;
			}
			if ((uintptr_t)pe >= (uintptr_t)end) {
				pe = end;
				done++;
			}
			if ((uintptr_t)p == (uintptr_t)pe) {
				break;
			}

			while (p < pe) {
				if ((bad=*p) != pat) {
					error((ulong*)p, pat, bad);
				}
				*p = ~pat;
				if (++k >= 32) {
					pat = lb;
					k = 0;
				} else {
					pat = pat << 1;
					pat |= sval;
				}
				p++;
			}

			do_tick();
		} while (!done);

		/* Since we already adjusted k and the pattern this
		 * code backs both up one step
		 */

		pat = lb;
		if ( 0 != (k = (k-1) & 31) ) {
			pat = (pat << k);
			if ( sval )
				pat |= ((sval << k) - 1);
		}
		k++;

		start = map_start;
		end = map_end;
		p = end -1;
		pe = end -1;
		done = 0;
		do {
			/* Check for underflow */
			if ((uintptr_t)(pe - SPINSZ) < (uintptr_t)pe) {
				pe -= SPINSZ;
			} else {
				pe = start;
			}
			if ((uintptr_t)pe <= (uintptr_t)start) {
				pe = start;
				done++;
			}
			if ((uintptr_t)p == (uintptr_t)pe) {
				break;
			}

			do {
				if ((bad=*p) != ~pat) {
					error((ulong*)p, ~pat, bad);
				}
				*p = pat;
				if (--k <= 0) {
					pat = hb;
					k = 32;
				} else {
					pat = pat >> 1;
					pat |= p3;
				}
			} while (p-- > pe);

			do_tick();
		} while (!done);
	}
}

/*
 * Test all of memory using modulo X access pattern.
 */

static void
modtst(int offset, int iter, ulong p1, ulong p2)
{
	int k, l, done;
	volatile ulong *pe;
	volatile ulong *start, *end;
	ulong bad;

	/* Display the current pattern */
	hprint(LINE_PAT, COL_PAT-2, p1);
	cprint(LINE_PAT, COL_PAT+6, "-");
	dprint(LINE_PAT, COL_PAT+7, offset, 2, 1);

	/* Write every nth location with pattern */
	start = map_start;
	end = map_end;
	pe = (ulong *)start;
	p = start+offset;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) >= (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}

		for (; p < pe; p += MOD_SZ) {
			*p = p1;
		}

		do_tick();
	} while (!done);

	/* Write the rest of memory "iter" times with the pattern complement */
	for (l=0; l<iter; l++) {
		start = map_start;
		end = map_end;
		pe = (ulong *)start;
		p = start;
		done = 0;
		k = 0;
		do {
			/* Check for overflow */
			if ((uintptr_t)(pe + SPINSZ) >= (uintptr_t)pe) {
				pe += SPINSZ;
			} else {
				pe = end;
			}
			if ((uintptr_t)pe >= (uintptr_t)end) {
				pe = end;
				done++;
			}
			if ((uintptr_t)p == (uintptr_t)pe) {
				break;
			}

			for (; p < pe; p++) {
				if (k != offset) {
					*p = p2;
				}
				if (++k > MOD_SZ-1) {
					k = 0;
				}
			}

			do_tick();
		} while (!done);
	}

	/* Now check every nth location */
	start = map_start;
	end = map_end;
	pe = (ulong *)start;
	p = start+offset;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ) >= (uintptr_t)pe) {
			pe += SPINSZ;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {

			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}

		for (; p < pe; p += MOD_SZ) {
			if ((bad=*p) != p1) {
				error((ulong*)p, p1, bad);
			}
		}

		do_tick();
	} while (!done);
	cprint(LINE_PAT, COL_PAT, "          ");
}


#if 0
/*
 * Test memory using block moves
 * Adapted from Robert Redelmeier's burnBX test
 */

static void
block_move(int iter)
{
	int i, done;
	ulong len;
	volatile ulong p, pe, pp;
	volatile ulong start, end;

	cprint(LINE_PAT, COL_PAT-2, "          ");

	/* Initialize memory with the initial pattern.  */
	start = (ulong)map_start;
#ifdef USB_WAR
	/* We can't do the block move test on low memory beacuase
	 * BIOS USB support clobbers location 0x410 and 0x4e0
	 */
	if (start < 0x4f0) {
		start = 0x4f0;
	}
#endif
	end = (ulong)map_end;
	pe = start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ*4) > (uintptr_t)pe) {
			pe += SPINSZ*4;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {

			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {

			break;
		}
		len  = ((ulong)pe - (ulong)p) / 64;
		asm __volatile__ (
			"jmp L100\n\t"

			".p2align 4,,7\n\t"
			"L100:\n\t"
			"movl %%eax, %%edx\n\t"
			"notl %%edx\n\t"
			"movl %%eax,0(%%edi)\n\t"
			"movl %%eax,4(%%edi)\n\t"
			"movl %%eax,8(%%edi)\n\t"
			"movl %%eax,12(%%edi)\n\t"
			"movl %%edx,16(%%edi)\n\t"
			"movl %%edx,20(%%edi)\n\t"
			"movl %%eax,24(%%edi)\n\t"
			"movl %%eax,28(%%edi)\n\t"
			"movl %%eax,32(%%edi)\n\t"
			"movl %%eax,36(%%edi)\n\t"
			"movl %%edx,40(%%edi)\n\t"
			"movl %%edx,44(%%edi)\n\t"
			"movl %%eax,48(%%edi)\n\t"
			"movl %%eax,52(%%edi)\n\t"
			"movl %%edx,56(%%edi)\n\t"
			"movl %%edx,60(%%edi)\n\t"
			"rcll $1, %%eax\n\t"
			"leal 64(%%edi), %%edi\n\t"
			"decl %%ecx\n\t"
			"jnz  L100\n\t"
			: "=D" (p)
			: "D" (p), "c" (len), "a" (1)
			: "edx"
			);
		do_tick();
	} while (!done);

	/* Now move the data around
	 * First move the data up half of the segment size we are testing
	 * Then move the data to the original location + 32 bytes
	 */
	start = (ulong)map_start;
#ifdef USB_WAR
	/* We can't do the block move test on low memory beacuase
	 * BIOS USB support clobbers location 0x410 and 0x4e0
	 */
	if (start < 0x4f0) {
		start = 0x4f0;
	}
#endif
	end = (ulong)map_end;
	pe = start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ*4) > (uintptr_t)pe) {
			pe += SPINSZ*4;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}
		pp = p + ((pe - p) / 2);
		len  = ((ulong)pe - (ulong)p) / 8;
		for(i=0; i<iter; i++) {
			asm __volatile__ (
				"cld\n"
				"jmp L110\n\t"

				".p2align 4,,7\n\t"
				"L110:\n\t"
				"movl %1,%%edi\n\t"
				"movl %0,%%esi\n\t"
				"movl %2,%%ecx\n\t"
				"rep\n\t"
				"movsl\n\t"
				"movl %0,%%edi\n\t"
				"addl $32,%%edi\n\t"
				"movl %1,%%esi\n\t"
				"movl %2,%%ecx\n\t"
				"subl $8,%%ecx\n\t"
				"rep\n\t"
				"movsl\n\t"
				"movl %0,%%edi\n\t"
				"movl $8,%%ecx\n\t"
				"rep\n\t"
				"movsl\n\t"
				:: "g" (p), "g" (pp), "g" (len)
				: "edi", "esi", "ecx"
				);
			do_tick();
		}
		p = pe;
	} while (!done);

	/* Now check the data
	 * The error checking is rather crude.  We just check that the
	 * adjacent words are the same.
	 */
	start = (ulong)map_start;
#ifdef USB_WAR
	/* We can't do the block move test on low memory beacuase
	 * BIOS USB support clobbers location 0x4e0 and 0x410
	 */
	if (start < 0x4f0) {
		start = 0x4f0;
	}
#endif
	end = (ulong)map_end;
	pe = start;
	p = start;
	done = 0;
	do {
		/* Check for overflow */
		if ((uintptr_t)(pe + SPINSZ*4) > (uintptr_t)pe) {
			pe += SPINSZ*4;
		} else {
			pe = end;
		}
		if ((uintptr_t)pe >= (uintptr_t)end) {
			pe = end;
			done++;
		}
		if ((uintptr_t)p == (uintptr_t)pe) {
			break;
		}
		asm __volatile__ (
			"jmp L120\n\t"

			".p2align 4,,7\n\t"
			"L120:\n\t"
			"movl (%%edi),%%ecx\n\t"
			"cmpl 4(%%edi),%%ecx\n\t"
			"jnz L121\n\t"

			"L122:\n\t"
			"addl $8,%%edi\n\t"
			"cmpl %%edx,%%edi\n\t"
			"jb L120\n"
			"jmp L123\n\t"

			"L121:\n\t"
			"pushl %%edx\n\t"
			"pushl 4(%%edi)\n\t"
			"pushl %%ecx\n\t"
			"pushl %%edi\n\t"
			"call error\n\t"
			"popl %%edi\n\t"
			"addl $8,%%esp\n\t"
			"popl %%edx\n\t"
			"jmp L122\n"
			"L123:\n\t"
			: "=D" (p)
			: "D" (p), "d" (pe)
			: "ecx"
			);
		do_tick();
	} while (!done);
}

#endif

/*
 * Test memory for bit fade.
 */
#define STIME 5400
static void
bit_fade(void)
{
	volatile ulong bad;
	volatile ulong *start,*end;
	ulong p1;

	/* Do -1 and 0 patterns */
	p1 = 0;
	while (1) {

		/* Display the current pattern */
		hprint(LINE_PAT, COL_PAT, p1);

		/* Initialize memory with the initial pattern.  */
		start = map_start;
		end = map_end;
		p = start;
		for (p=start; p<end; p++) {
			*p = p1;
		}
		do_tick();
		/* Snooze for 90 minutes */
		sleep (STIME);

		/* Make sure that nothing changed while sleeping */
		start = map_start;
		end = map_end;
		p = start;
		for (p=start; p<end; p++) {
			if ((bad=*p) != p1) {
				error((ulong*)p, p1, bad);
			}
		}
		do_tick();

		if (p1 == 0) {
			p1=-1;
		} else {
			break;
		}
	}
}

static int
runtest(const struct tseq *t)
{
	int i,j,c_iter;
	ulong p0, p1, p2;
   
	printf("%s\n", t->msg);
   
	c_iter = t->iter;
	errors = 0;

	switch (t->pat) {
		/* Now do the testing according to the selected pattern */
	case 0:	/* Moving inversions, all ones and zeros (test #2) */
		p1 = 0;
		p2 = ~p1;
		movinv1(c_iter,p1,p2);
	
		/* Switch patterns */
		p2 = p1;
		p1 = ~p2;
		movinv1(c_iter,p1,p2);
		break;
		
	case 1: /* Moving inversions, 8 bit walking ones and zeros (test #3) */
		p0 = 0x80;
		for (i=0; i<8; i++, p0=p0>>1) {
			p1 = p0 | (p0<<8) | (p0<<16) | (p0<<24);
			p2 = ~p1;
			movinv1(c_iter,p1,p2);
	
			/* Switch patterns */
			p2 = p1;
			p1 = ~p2;
			movinv1(c_iter,p1,p2);
		}
		break;

	case 2: /* Moving inversions, 32 bit shifting pattern (test #6) */
		for (i=0, p1=1; p1; p1=p1<<1, i++) {
			movinv32(c_iter,p1, 1, 0x80000000, 0, i);
			movinv32(c_iter,~p1, 0xfffffffe,
				 0x7fffffff, 1, i);
		}
		break;

	case 3: /* Modulo 20 check, all ones and zeros (unused) */
		p1=0;
		for (i=0; i<MOD_SZ; i++) {
			p2 = ~p1;
			modtst(i, c_iter, p1, p2);

			/* Switch patterns */
			p2 = p1;
			p1 = ~p2;
			modtst(i, c_iter, p1,p2);
		}
		break;

	case 4: /* Modulo 20 check, 8 bit pattern (unused) */
		p0 = 0x80;
		for (j=0; j<8; j++, p0=p0>>1) {
			p1 = p0 | (p0<<8) | (p0<<16) | (p0<<24);
			for (i=0; i<MOD_SZ; i++) {
				p2 = ~p1;
				modtst(i, c_iter, p1, p2);

				/* Switch patterns */
				p2 = p1;
				p1 = ~p2;
				modtst(i, c_iter, p1, p2);
			}
		}
		break;
		
	case 5: /* Address test, walking ones (test #0) */
		addr_tst1();
		break;

	case 6: /* Address test, own address (test #1) */
		addr_tst2();
		break;

	case 7: /* Block move (test #5) */
#if 0
		block_move(c_iter);
#endif
		break;
	case 8: /* Bit fade test (test #9) */
		bit_fade();
		break;
	case 9: /* Random Data Sequence (test #7) */
		for (i=0; i < c_iter; i++) {
			movinvr();
		}
		break;
	case 10: /* Random Data (test #4) */
		for (i=0; i < c_iter; i++) {
			p1 = rand();
			p2 = ~p1;
			movinv1(2,p1,p2);
		}
		break;

	case 11: /* Modulo 20 check, Random pattern (test #8) */
		for (j=0; j<c_iter; j++) {
			p1 = rand();
			for (i=0; i<MOD_SZ; i++) {
				p2 = ~p1;
				modtst(i, 2, p1, p2);

				/* Switch patterns */
				p2 = p1;
				p1 = ~p2;
				modtst(i, 2, p1, p2);
			}
		}
		break;
	}
	
	printf("\nERRORS %lu\n", errors);

	return errors;
}

int
do_memtest(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i, ret;
   
	ret = 0;
	abort_memtest = 0;
   
	if (argc < 3) {
		return cmd_usage(cmdtp);
	}
   
	map_start = (void*)simple_strtoul(argv[1], NULL, 16);
	map_end = (void*)map_start + simple_strtoul(argv[2], NULL, 16);
   
	if (map_end <= map_start) {
		return cmd_usage(cmdtp);
	}
   
	if (argc >= 4) {
		for (i=3; i<argc; ++i) {
			int test = simple_strtoul(argv[i], NULL, 0);
         
			if (test >= NTESTS)
				continue;
         
			ret += runtest(&tseq[test]);
			if (abort_memtest)
				break;
		}
	}else{
		for (i=0; i<NTESTS; ++i) {
			ret += runtest(&tseq[i]);
			if (abort_memtest)
				break;
		}
	}

	printf("\nTOTAL ERRORS %u\n", ret);

	return ret;
}

U_BOOT_CMD(
	memtest, 32, 0, do_memtest,
	"memory test using memtest86 algorithms",
	"startaddr length [tests...]\n"
	" 0 = [Address test, walking ones]\n"
	" 1 = [Address test, own address]\n"
	" 2 = [Moving inversions, ones & zeros]\n"
	" 3 = [Moving inversions, 8 bit pattern]\n"
	" 4 = [Moving inversions, random pattern]\n"
	" 5 = [Moving inversions, 32 bit pattern]\n"
	" 6 = [Random number sequence]\n"
	" 7 = [Modulo 20, Random pattern]\n"
	);
