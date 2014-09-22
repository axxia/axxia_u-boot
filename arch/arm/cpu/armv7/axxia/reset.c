#include <common.h>
#include <asm/io.h>

void reset_cpu(ulong ignored)
{
	/*
	  Chip Reset
	*/

	writel(0x000000ab, 0x90031000); /* Access Key */
	writel(0x00000040, 0x90031004); /* Internal Boot, 0xffff0000 Target */
 	writel(0x80000000, 0x9003180c);	/* Set ResetReadDone */
 	writel(0x00080802, 0x90031008);	/* Chip Reset */

	printf("Reset failed!\n"); /* Should never get here... */
}
