/******************************************************************************************
  Filename    : Memory_Map.ld
  
  Core        : T-Head XuanTie C906 (RV64)
  
  SoC         : CVITEK CV1800B (Milk-V Duo)
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 25.02.2026
  
  Description : Linker Descriptor file
  
******************************************************************************************/

/******************************************************************************************
 ELF Entrypoint
******************************************************************************************/
ENTRY(_start)

/******************************************************************************************
 Globals
******************************************************************************************/
__STACK_SIZE_CORE0 = 1K;
__STACK_SIZE_CORE1 = 1K;

/******************************************************************************************
 Memory configuration
******************************************************************************************/
MEMORY
{
  ROM(rx)           : ORIGIN = 0x80000000, LENGTH = 2M
  RAM(rwx)          : ORIGIN = 0x80200000, LENGTH = 2M
  RAM_NO_CACHE(rwx) : ORIGIN = 0x80400000, LENGTH = 2M
}

/******************************************************************************************
 Sections definition
******************************************************************************************/
SECTIONS
{
   .text :
   {
    PROVIDE(__CODE_BASE_ADDRESS = .);
    *(.boot)
    *(.text)
   } > ROM

  /* Read-only data (.rodata) */
  .rodata : ALIGN(4)
  {
    PROVIDE(__RODATA_BASE_ADDRESS = .);
    *(.rodata)
  } > ROM

 /* Section for constructors */
  .ctors : ALIGN(8)
  {
    PROVIDE(__CTOR_LIST__  = .);
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    QUAD(-1) ;
    PROVIDE(__CTOR_END__  = .);
    . = ALIGN(8);
  }  > ROM


  /* Section for destructors */
  .dtors : ALIGN(8)
  {
    PROVIDE(__DTOR_LIST__  = .);
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array))
    QUAD(-1) ;
    PROVIDE(__DTOR_END__  = .);
    . = ALIGN(8);
  } > ROM

  /* Runtime clear table */
  .clear_sec : ALIGN(8)
  {
    PROVIDE(__RUNTIME_CLEAR_TABLE = .) ;
    QUAD(ADDR(.bss));   QUAD(SIZEOF(.bss));
    QUAD(ADDR(.non_cacheable_bss));   QUAD(SIZEOF(.non_cacheable_bss));
    QUAD(ADDR(.sbss));  QUAD(SIZEOF(.sbss));
    QUAD(-1);           QUAD(-1);
    . = ALIGN(8);
  } > ROM

  /* Runtime copy table */
  .copy_sec : ALIGN(8)
  {
    PROVIDE(__RUNTIME_COPY_TABLE = .) ;
    QUAD(LOADADDR(.data));   QUAD(ADDR(.data));   QUAD(SIZEOF(.data));
    QUAD(LOADADDR(.non_cacheable_data));   QUAD(ADDR(.non_cacheable_data));   QUAD(SIZEOF(.non_cacheable_data));
    QUAD(LOADADDR(.sdata));  QUAD(ADDR(.sdata));  QUAD(SIZEOF(.sdata));
    QUAD(-1);                QUAD(-1);            QUAD(-1);
    . = ALIGN(8);
    PROVIDE(__CODE_END_ADDRESS = .);
  } > ROM 

  /* The ROM-to-RAM initialized data section */
  .data : ALIGN(8) 
  {
    *(.data)
    *(.data*)
    . = ALIGN(8);
  } > RAM  AT>ROM

  .non_cacheable_data : ALIGN(8)
  {
    *(.non_cacheable_data)
    . = ALIGN(8);
  } > RAM_NO_CACHE  AT>ROM
  
  /* The uninitialized (zero-cleared) data section */
  .bss : ALIGN(8)
  {
    *(.bss)
    *(.bss*)
    . = ALIGN(8);
  } > RAM

  .non_cacheable_bss (NOLOAD) : ALIGN(8)
  {
    *(.non_cacheable_bss)
    . = ALIGN(8);
  } > RAM_NO_CACHE

  /* The initialized Small Data Area (SDA) */
  .sdata : ALIGN(8) 
  {
    PROVIDE(__small_data_start = .);
    *(.sdata)
    . = ALIGN(8);
  } > RAM  AT>ROM

  /* The uninitialized (zero-cleared) Small Data Area (SDA) */
  .sbss : ALIGN(8)
  {
    *(.sbss)
    . = ALIGN(8);
    PROVIDE(__small_data_end = .);
  } > RAM

  /* stack definition */
  .stack_core0 :
  {
    PROVIDE(__CORE0_STACK_BOTTOM = .) ;
    . = ALIGN(MAX(__STACK_SIZE_CORE0 , .), 8);
    PROVIDE(__CORE0_STACK_TOP = .) ;
  } > RAM

  .stack_core1 :
  {
    PROVIDE(__CORE1_STACK_BOTTOM = .) ;
    . = ALIGN(MAX(__STACK_SIZE_CORE1 , .), 8);
    PROVIDE(__CORE1_STACK_TOP = .) ;
  } > RAM

}
__global_pointer$ = __small_data_start + (__small_data_end - __small_data_start)/2;

/* MMU level1 page tables */
MMU_PT_LEVEL_1_0x8000_0000 = ((mmu_page_table_level_1_0x8000_0000 >> 12) << 10) | 0x01;
MMU_PT_LEVEL_1_0xC000_0000 = ((mmu_page_table_level_1_0xc000_0000 >> 12) << 10) | 0x01;
