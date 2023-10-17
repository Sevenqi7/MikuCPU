/* The following TEXT start address leaves space for the monitor
   workspace. */
ENTRY(_start)
STARTUP("start.o");
OUTPUT_FORMAT(elf32-loongarch);
GROUP(-lpmon)
SEARCH_DIR(.)
__DYNAMIC  =  0;
/*
 * Allocate the stack to be at the top of memory, since the stack
 * grows down
 */
/* PROVIDE (__stack = 0);  */
/* PROVIDE (__global = 0); */

/*
 * Initalize some symbols to be zero so we can reference them in the
 * crt0 without core dumping. These functions are all optional, but
 * we do this so we can have our crt0 always use them if they exist. 
 * This is so BSPs work better when using the crt0 installed with gcc.
 * We have to initalize them twice, so we multiple object file
 * formats, as some prepend an underscore.
 */
PROVIDE (hardware_exit_hook = 0);
PROVIDE (hardware_hazard_hook = 0);
PROVIDE (hardware_init_hook = 0);
PROVIDE (software_init_hook = 0);

SECTIONS
{	
  . = 0x1c000000;
  .start : {
    _start = . ;
	kernel_entry = . ;
    start.o(.text)
  }
  .main : {
	*(.text)
    *(.text.*)
    KEEP (*(.fini))
     etext  =  .;
     _etext  =  .;
  }
  
  .eh_frame_hdr : { *(.eh_frame_hdr) }
  .eh_frame : { KEEP (*(.eh_frame)) }
  .gcc_except_table : { *(.gcc_except_table) }
  .jcr : { KEEP (*(.jcr)) }
  .ctors    :
  {
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

    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */

    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }

  .dtors    :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }

  . = 0x1000;
  .ex_table_base : {
	  _ex_table_base_start = .;
	  . += 0x500;
	  _ex_table_base_end = .;
  }

  . = ALIGN(4);
  .pmon_vector : {
	  _pmon_vector_start = .;
	  . += 0x500;
	  _pmon_vector_end = .;
  }

  . = ALIGN(16);
  .rodata : {
    *(.rdata)
    *(.rodata)
    *(.rodata.*)
  }

  . = ALIGN(16);
  .data : {
    *(.data)
    *(.data.*)
  }

  . = ALIGN(16);
  .got : {
	*(.got)
  }

  . = ALIGN(8);
  .bss : {
    _bss_start = . ;
    *(.bss)
    *(.bss.*)
    *(.sbss)
    *(.sbss.*)
    *(COMMON)
	_bss_end = . ;
  }

  . = ALIGN(8);
  .heap : {
     __heap_start = .;
     . += 0x100000;
     __heap_end = .;
  }

  . = ALIGN(8);
  .stack : {
     __stack_end = .;
     . += 0x100000;
     __stack_start = .;
  }

}
