#include <common.h>
#include <asm/io.h>

void reset_cpu(ulong ignored)
{
	/*
	  Chip Reset
	*/

	/* Forcing Gen1 speed before reset such that endpoint
	 * switches to Gen1 and then if Gen2 speed change is initiated
	 * from RootComplex, it works
	 */
	writel(0x00010041, 0xa0120090); /* PEI0 Gen 1 speed */
	writel(0x00010000, 0xa012117c);
	writel(0x00010041, 0xa0130090); /* PEI1 Gen 1 speed */
	writel(0x00010000, 0xa013117c);
	writel(0x000000ab, 0x90031000); /* Access Key */
	writel(0x00000040, 0x90031004); /* Internal Boot, 0xffff0000 Target */
 	writel(0x80000000, 0x9003180c);	/* Set ResetReadDone */
 	writel(0x00080802, 0x90031008);	/* Chip Reset */

	printf("Reset failed!\n"); /* Should never get here... */
}
