MEMORY { .lsm : ORIGIN = 0x20000000, LENGTH = 0x39000 }

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

OUTPUT_ARCH(arm)

ENTRY(_start)

SECTIONS
{
	.text :
	{
		arch/arm/cpu/armv7/start.o (.text);
		*(.text*);
	} >.lsm

	. = ALIGN(4);

	__start___ex_table = .;
	__ex_table :
	{
		*(__ex_table)
	}
	__stop___ex_table = .;

	.data :
	{
		*(.rodata*)
		*(.sdata*)
		*(.data*)
	} > .lsm

	.got2 :
	{
		*(.got2*)
	} > .lsm

	.fixup :
	{
		*(.fixup)
	} > .lsm

	.eh_frame :
	{
		*(.eh_frame)
	} > .lsm

	__end_of_spl = .;

	. = ALIGN(4);
	__image_copy_end = .;
	_end = .;


	/*
	 * Provide space for a page table (0x5000 bytes).
 	 */

	.pagetable :
	{
		. = ALIGN(0x4000);
		__page_table_start = .;
		. += 0x5000;
		__page_table_end = .;
	} >.lsm

	.bss :
	{
		. = ALIGN(4);
		__bss_start = .;
		*(.bss*)
		. = ALIGN(4);
		__bss_end__ = .;
	} >.lsm
}
