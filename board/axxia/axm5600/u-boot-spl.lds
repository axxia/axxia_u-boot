OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
. = 0x00000000;
. = ALIGN(4);
.text :
{
__image_copy_start = .;
*(.vectors)
arch/arm/cpu/armv8/start.o (.text*)

/*
	Include the secure monitor.
*/
. = ALIGN(4096);
_bl31_start = .;
KEEP(bl31.o (.monitor*))
_bl31_end = .;

*(.text*)
}
. = ALIGN(4);
.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

. = ALIGN(4);
.data : {
	*(.data*)
}

. = ALIGN(4);
. = .;
__image_copy_end = .;
.rel.dyn : {
__rel_dyn_start = .;
*(.rel*)
__rel_dyn_end = .;
}
.end :
{
*(.__end)
}
_image_binary_end = .;
.bss __rel_dyn_start (OVERLAY) : {
__bss_start = .;
*(.bss*)
. = ALIGN(4);
__bss_end = .;
}
.dynsym _image_binary_end : { *(.dynsym) }
.dynbss : { *(.dynbss) }
.dynstr : { *(.dynstr*) }
.dynamic : { *(.dynamic*) }
.hash : { *(.hash*) }
.plt : { *(.plt*) }
.interp : { *(.interp*) }
.gnu : { *(.gnu*) }
.ARM.exidx : { *(.ARM.exidx*) }
}
ASSERT(__image_copy_end - __image_copy_start < (0x30000), "SPL image too big");
