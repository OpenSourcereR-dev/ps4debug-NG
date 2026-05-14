.intel_syntax noprefix
.text

.global _start
.hidden _start
_start:
	and		rsp, -16            # 16-byte align the stack (SysV ABI; the loader's
                                # alignment isn't guaranteed, and clang/libc++/
                                # Sony code uses aligned-SSE on the stack)
	lea		rdi, [rip + _start] # rdi = real load base (this -pie .bin is linked
                                # at 0; _start is at offset 0). Pass it to the
                                # self-relocator (avoids any GOT round-trip).
	call	__self_relocate     # apply .rela.dyn RELATIVE relocs against rdi
	call	_main               # post-`call`: rsp%16==8 -> _main's prologue makes ==0
1:	jmp		1b                  # _main never returns; safety loop
