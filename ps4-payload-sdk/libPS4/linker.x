OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

ENTRY(_start)

PHDRS
{
	code_seg  PT_LOAD;
	rdata_seg PT_LOAD;
	data_seg  PT_LOAD;
	bss_seg   PT_LOAD;
}

SECTIONS
{
	/* Linked at base 0: a normal -pie image. crt0.s -> __self_relocate() slides
	 * the R_X86_64_RELATIVE entries (.rela.dyn) to the real load base. */
	. = 0;

	.text : {
		*(.text.start)
		*(.text*)
	} : code_seg

	.init_array : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
		KEEP (*(.init_array .ctors))
		PROVIDE_HIDDEN (__init_array_end = .);
	} : code_seg
	.fini_array : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
		KEEP (*(.fini_array .dtors))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} : code_seg

	.rodata : {
		*(.rodata)
		*(.rodata*)
	} : rdata_seg

	.eh_frame_hdr : {
		PROVIDE_HIDDEN (__eh_frame_hdr_start = .);
		KEEP (*(.eh_frame_hdr))
		PROVIDE_HIDDEN (__eh_frame_hdr_end = .);
	} : rdata_seg
	.eh_frame : {
		PROVIDE_HIDDEN (__eh_frame_start = .);
		KEEP (*(.eh_frame))
		PROVIDE_HIDDEN (__eh_frame_end = .);
	} : rdata_seg
	.gcc_except_table : { *(.gcc_except_table .gcc_except_table.*) } : rdata_seg

	/* keep the dynamic RELATIVE relocations in a loadable section so they survive
	 * objcopy -O binary; __self_relocate() walks [__rela_start, __rela_end). */
	.rela.dyn : {
		PROVIDE_HIDDEN (__rela_start = .);
		*(.rela.init_array) *(.rela.fini_array)
		*(.rela.data .rela.data.* .rela.data.rel.ro .rela.data.rel.ro.*)
		*(.rela.got) *(.rela.bss) *(.rela.text .rela.text.*) *(.rela.rodata .rela.rodata.*)
		*(.rela.dyn) *(.rela) *(.rela.*)
		PROVIDE_HIDDEN (__rela_end = .);
	} : rdata_seg

	.data : {
		*(.data)
		*(.data.*)
	} : data_seg
	.data.rel.ro : { *(.data.rel.ro .data.rel.ro.* .data.rel.ro.local*) } : data_seg
	.got : { *(.got) *(.got.plt) } : data_seg

	.bss : {
		*(.bss)
		*(.bss.*)
		*(COMMON)
	} : bss_seg

	/DISCARD/ : {
		*(.comment) *(.note .note.*)
		*(.dynamic) *(.dynsym) *(.dynstr) *(.hash) *(.gnu.hash)
		*(.interp) *(.gnu.version) *(.gnu.version_d) *(.gnu.version_r)
		*(.dynbss) *(.plt) *(.plt.*) *(.iplt)
		*(.rela.plt) *(.rela.iplt)
	}
}
