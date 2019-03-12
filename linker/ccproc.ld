/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
*
*  ----------------------------------------------------------------------
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ChipCraft Sp. z o.o. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
* -------------------------------------------------------------------- */

/**
 * @addtogroup      CCCPU
 * @{
 *
 * @file            ccproc.ld
 * @brief           Linker script for CC Processor
 *
 * @author          Rafal Harabien
 */

ENTRY(__start)

/* Memory Space Definitions */
MEMORY
{
    rom   (rx ) : ORIGIN = 0x00000000, LENGTH = 0x20000000
    ram   (rwx) : ORIGIN = 0x40000000, LENGTH = 0x40000000
    spram (rwx) : ORIGIN = 0x20000000, LENGTH = 0x10000000
}

/* Output Sections Definitions */
SECTIONS
{
  .text :
  {
    _stext = .;
    *(.boot .boot.*)
    KEEP (*(SORT_NONE(.init)))
    *(.text .text.* .gnu.linkonce.t.*)
    KEEP (*(SORT_NONE(.fini)))
  } > rom

  .rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) } > rom
  .eh_frame_hdr : { *(.eh_frame_hdr) *(.eh_frame_entry .eh_frame_entry.*) } > rom
  .eh_frame       :  { KEEP (*(.eh_frame)) *(.eh_frame.*) } > rom
  .gcc_except_table   :  { *(.gcc_except_table .gcc_except_table.*) } > rom
  .gnu_extab   :  { *(.gnu_extab*) } > rom
  .jcr :  { *(.jcr*) } > rom

  .init_data :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);

    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    PROVIDE_HIDDEN (__init_array_end = .);

    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);

    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))

    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))

    _etext = .;
    _data_load = .;
  } > rom

  .data : AT (_data_load) {
    . = ALIGN(4);
    HIDDEN(_gp = ALIGN(16) + 0x7ff0);
    _sdata = .;

    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
    *(.sdata .sdata.* .gnu.linkonce.s.*)

    *(.tm_clone_table)

    /* Keep section for locks aligned to max cache line size */
    . = ALIGN(128);
    *(.locks)
    . = ALIGN(128);

    _edata = .;

  } > ram

  _spram_data_load = _data_load + SIZEOF(.data);
  .spram_data : AT (_spram_data_load) {
    _sspram_data = .;
    *(.spram_data)
    _espram_data = .;
  } > spram

  .bss (NOLOAD) :
  {
    _sbss = .;

    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(.COMMON)
    *(COMMON)

    _ebss = .;
  } > ram

  .heap (NOLOAD) :
  {
    PROVIDE(_sheap = .);
  } > ram

  .spram_bss (NOLOAD) : {
    _sspram_bss = .;
    *(.spram_bss)
    _espram_bss = .;
  } > spram

  /* Discarded input sections */
  /DISCARD/ :
  {
    *(.MIPS.abiflags)
    *(.rel.dyn)
  }
}

/* @} */
