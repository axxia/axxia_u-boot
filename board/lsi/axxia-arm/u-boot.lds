OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
	. = 0x00000000;

	.text :
	{
		__image_copy_start = .;
		arch/arm/cpu/armv7/start.o (.text*)
		*(.text*)
	}

	/*
	 * Space for spin tables (0x20 bytes per core, 16 * 0x20 = 0x200).
	 */

	. = ALIGN(0x4);
	__spin_table_start = .;
	. += 0x200;
	__spin_table_end = .;  


	/*
	 * Space for page tables.
	 */

	. = ALIGN(0x4000);
	__page_table_start = .;
	. += 0x5000;
	__page_table_end = .;

	. = ALIGN(4);
	.rodata :
	{
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	}

	. = ALIGN(4);
	.data :
	{
		*(.data*)
	}


	. = ALIGN(4);
	.u_boot_list :
	{
		*(SORT(.u_boot_list*));
	}

	. = ALIGN(4);
	__image_copy_end = .;

	.rel.dyn :
	{
		__rel_dyn_start = .;
		*(.rel*)
		__rel_dyn_end = .;
	}

	.dynsym :
	{
		__dynsym_start = .;
		*(.dynsym)
	}

	_end = .;

	.bss __rel_dyn_start (OVERLAY) :
	{
		__bss_start = .;
		*(.bss*)
		. = ALIGN(4);
		__bss_end__ = .;
	}

	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
}
