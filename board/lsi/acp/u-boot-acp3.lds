/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

OUTPUT_ARCH(powerpc)
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */
SECTIONS
{
  .resetvec 0x00000000 :
  {
    *(.resetvec)
  } = 0xffff

  . = 0x1000;
  PROVIDE (_ose_strings_0 = .);
  .ose_strings_0_section : { *(.ose_strings_0_section) }

  . = 0x1400;
  PROVIDE (_ose_strings_1 = .);
  .ose_strings_1_section : { *(.ose_strings_1_section) }

  . = 0x1800;
  PROVIDE (_ose_strings_2 = .);
  .ose_strings_2_section : { *(.ose_strings_2_section) }

  . = 0x1c00;
  PROVIDE (_ose_strings_3 = .);
  .ose_strings_3_section : { *(.ose_strings_3_section) }

  .bootpg 0x00002000 :
  {
    arch/powerpc/cpu/ppc4xx/start.o	(.bootpg)
  } = 0xffff

  /* Read-only sections, merged into text segment: */
  . = + SIZEOF_HEADERS;
  .interp : { *(.interp) }
  .hash          : { *(.hash)		}
  .dynsym        : { *(.dynsym)		}
  .dynstr        : { *(.dynstr)		}
  .rel.text      : { *(.rel.text)		}
  .rela.text     : { *(.rela.text)	}
  .rel.data      : { *(.rel.data)		}
  .rela.data     : { *(.rela.data)	}
  .rel.rodata    : { *(.rel.rodata)	}
  .rela.rodata   : { *(.rela.rodata)	}
  .rel.got       : { *(.rel.got)		}
  .rela.got      : { *(.rela.got)		}
  .rel.ctors     : { *(.rel.ctors)	}
  .rela.ctors    : { *(.rela.ctors)	}
  .rel.dtors     : { *(.rel.dtors)	}
  .rela.dtors    : { *(.rela.dtors)	}
  .rel.bss       : { *(.rel.bss)		}
  .rela.bss      : { *(.rela.bss)		}
  .rel.plt       : { *(.rel.plt)		}
  .rela.plt      : { *(.rela.plt)		}
  .init          : { *(.init)	}
  .plt : { *(.plt) }
  .text      :
  {
    /* WARNING - the following is hand-optimized to fit within	*/
    /* the sector layout of our flash chips!	XXX FIXME XXX	*/

    arch/powerpc/cpu/ppc4xx/start.o	(.text)
    board/lsi/acp/acp_init.o	(.text)

    *(.text)
    *(.fixup)
    *(.got1)
  }
  _etext = .;
  PROVIDE (etext = .);

  . = 0x40000;
  __acp_osg_cores = .;
  .acp_osg_cores_section : { *(.acp_osg_cores_section) }
  . += 0x100;

  __acp_osg_groups = .;
  .acp_osg_groups_section : { *(.acp_osg_groups_section) }
  . += 0x100;

  __acp_system_section = .;
  .acp_system_section : { *(.acp_system_secion) }
  . += 0x100;

  . = ALIGN(256);
  _core_copy_beginning = .;

  .rodata    :
  {
    *(.rodata)
    *(.rodata1)
    *(.rodata.str1.4)
    *(.eh_frame)
  }
  .fini      : { *(.fini)    } =0
  .ctors     : { *(.ctors)   }
  .dtors     : { *(.dtors)   }

  /* Read-write section, merged into data segment: */
  . = (. + 0x00FF) & 0xFFFFFF00;
  _erotext = .;
  PROVIDE (erotext = .);
  .reloc   :
  {
    *(.got)
    _GOT2_TABLE_ = .;
    *(.got2)
    _FIXUP_TABLE_ = .;
    *(.fixup)
  }
  __got2_entries = (_FIXUP_TABLE_ - _GOT2_TABLE_) >>2;
  __fixup_entries = (. - _FIXUP_TABLE_)>>2;

  .data    :
  {
    *(.data)
    *(.data1)
    *(.sdata)
    *(.sdata2)
    *(.dynamic)
    CONSTRUCTORS
  }

  . = .;
  __u_boot_cmd_start = .;
  .u_boot_cmd : { *(.u_boot_cmd) }
  __u_boot_cmd_end = .;

  . = .;
  __start___ex_table = .;
  __ex_table : { *(__ex_table) }
  __stop___ex_table = .;

  . = ALIGN(256);
  __init_begin = .;
  .text.init : { *(.text.init) }
  .data.init : { *(.data.init) }
  . = ALIGN(256);
  __init_end = .;
  _core_copy_end = .;

  PROVIDE (_bss_start = .);
  .bss (NOLOAD)       :
  {
   *(.sbss*)
   *(.scommon*)
   *(.dynbss*)
   *(.bss*)
   *(COMMON)
  }
  . = ALIGN(256);
  PROVIDE (_bss_end = . );

  . = ALIGN(256);
  _core_copy_core0 = .;
  . = (. + (_core_copy_end - _core_copy_beginning));

  . = ALIGN(256);
  _core_copy_core1 = .;
  . = (. + (_core_copy_end - _core_copy_beginning));

  . = ALIGN(256);
  _core_copy_core2 = .;
  . = (. + (_core_copy_end - _core_copy_beginning));

  . = ALIGN(256);
  _core_copy_core3 = .;
  . = (. + (_core_copy_end - _core_copy_beginning));

  _end = . ;
  PROVIDE (end = .);
}
