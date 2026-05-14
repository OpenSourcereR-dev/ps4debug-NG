// SPDX-License-Identifier: GPL-3.0-only

#include <stdint.h>

typedef struct {
    uint64_t r_offset;
    uint64_t r_info;
    int64_t  r_addend;
} __attribute__((packed)) Elf64_Rela;

#define R_X86_64_RELATIVE 8

extern Elf64_Rela __rela_start[] __attribute__((visibility("hidden"), weak));
extern Elf64_Rela __rela_end[]   __attribute__((visibility("hidden"), weak));

__attribute__((no_stack_protector, used))
void __self_relocate(uintptr_t base)
{
    Elf64_Rela *r = __rela_start;
    Elf64_Rela *e = __rela_end;
    if (r) {
        for (; r < e; r++) {
            if ((uint32_t)(r->r_info & 0xffffffffu) == R_X86_64_RELATIVE) {
                *(uint64_t *)(base + r->r_offset) = base + (uint64_t)r->r_addend;
            }
        }
    }
}
