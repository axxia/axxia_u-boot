MEMORY { .sram : ORIGIN = 0x20000000, LENGTH = 0x19000 }
MEMORY { .sdram : ORIGIN = 0x84000000, LENGTH = 0x100000 }
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
 .text :
 {
  __start = .;
  arch/arm/cpu/armv7/start.o (.text)
  *(.text*)
 } >.sram
 . = ALIGN(4);
 .rodata : { *(SORT_BY_ALIGNMENT(.rodata*)) } >.sram
 . = ALIGN(4);
 .data : { *(SORT_BY_ALIGNMENT(.data*)) } >.sram
 .u_boot_list : {
  *(SORT(.u_boot_list*));
 }
 . = ALIGN(4);
 __image_copy_end = .;
 _end = .;
 .bss :
 {
  . = ALIGN(4);
  __bss_start = .;
  *(.bss*)
  . = ALIGN(4);
  __bss_end__ = .;
 } >.sdram
}
