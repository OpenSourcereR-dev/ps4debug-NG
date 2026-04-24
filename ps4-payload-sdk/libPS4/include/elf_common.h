
#ifndef ELF_COMMON_H
#define ELF_COMMON_H

typedef struct {
  uint32_t n_namesz;
  uint32_t n_descsz;
  uint32_t n_type;
} Elf_Note;

typedef struct {
  uint32_t gh_nbuckets;
  uint32_t gh_symndx;
  uint32_t gh_maskwords;
  uint32_t gh_shift2;
} Elf_GNU_Hash_Header;

#define EI_MAG0 0
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_OSABI 7
#define EI_ABIVERSION 8
#define OLD_EI_BRAND 8
#define EI_PAD 9
#define EI_NIDENT 16

#define ELFMAG0 0x7f
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'
#define ELFMAG "\177ELF"
#define SELFMAG 4

#define EV_NONE 0
#define EV_CURRENT 1

#define ELFCLASSNONE 0
#define ELFCLASS32 1
#define ELFCLASS64 2

#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

#define ELFOSABI_NONE 0
#define ELFOSABI_HPUX 1
#define ELFOSABI_NETBSD 2
#define ELFOSABI_LINUX 3
#define ELFOSABI_HURD 4
#define ELFOSABI_86OPEN 5
#define ELFOSABI_SOLARIS 6
#define ELFOSABI_AIX 7
#define ELFOSABI_IRIX 8
#define ELFOSABI_FREEBSD 9
#define ELFOSABI_TRU64 10
#define ELFOSABI_MODESTO 11
#define ELFOSABI_OPENBSD 12
#define ELFOSABI_OPENVMS 13
#define ELFOSABI_NSK 14
#define ELFOSABI_AROS 15
#define ELFOSABI_ARM 97
#define ELFOSABI_STANDALONE 255

#define ELFOSABI_SYSV ELFOSABI_NONE
#define ELFOSABI_MONTEREY ELFOSABI_AIX

#define IS_ELF(ehdr) ((ehdr).e_ident[EI_MAG0] == ELFMAG0 && \
                      (ehdr).e_ident[EI_MAG1] == ELFMAG1 && \
                      (ehdr).e_ident[EI_MAG2] == ELFMAG2 && \
                      (ehdr).e_ident[EI_MAG3] == ELFMAG3)

#define ET_NONE 0
#define ET_REL 1
#define ET_EXEC 2
#define ET_DYN 3
#define ET_CORE 4
#define ET_LOOS 0xfe00
#define ET_HIOS 0xfeff
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

#define EM_NONE 0
#define EM_M32 1
#define EM_SPARC 2
#define EM_386 3
#define EM_68K 4
#define EM_88K 5
#define EM_860 7
#define EM_MIPS 8
#define EM_S370 9
#define EM_MIPS_RS3_LE 10
#define EM_PARISC 15
#define EM_VPP500 17
#define EM_SPARC32PLUS 18
#define EM_960 19
#define EM_PPC 20
#define EM_PPC64 21
#define EM_S390 22
#define EM_V800 36
#define EM_FR20 37
#define EM_RH32 38
#define EM_RCE 39
#define EM_ARM 40
#define EM_SH 42
#define EM_SPARCV9 43
#define EM_TRICORE 44
#define EM_ARC 45
#define EM_H8_300 46
#define EM_H8_300H 47
#define EM_H8S 48
#define EM_H8_500 49
#define EM_IA_64 50
#define EM_MIPS_X 51
#define EM_COLDFIRE 52
#define EM_68HC12 53
#define EM_MMA 54
#define EM_PCP 55
#define EM_NCPU 56
#define EM_NDR1 57
#define EM_STARCORE 58
#define EM_ME16 59
#define EM_ST100 60
#define EM_TINYJ 61
#define EM_X86_64 62
#define EM_AMD64 EM_X86_64
#define EM_PDSP 63
#define EM_FX66 66
#define EM_ST9PLUS 67

#define EM_ST7 68

#define EM_68HC16 69
#define EM_68HC11 70
#define EM_68HC08 71
#define EM_68HC05 72
#define EM_SVX 73
#define EM_ST19 74
#define EM_VAX 75
#define EM_CRIS 76

#define EM_JAVELIN 77

#define EM_FIREPATH 78
#define EM_ZSP 79
#define EM_MMIX 80
#define EM_HUANY 81

#define EM_PRISM 82
#define EM_AVR 83
#define EM_FR30 84
#define EM_D10V 85
#define EM_D30V 86
#define EM_V850 87
#define EM_M32R 88
#define EM_MN10300 89
#define EM_MN10200 90
#define EM_PJ 91
#define EM_OPENRISC 92
#define EM_ARC_A5 93
#define EM_XTENSA 94
#define EM_VIDEOCORE 95
#define EM_TMM_GPP 96

#define EM_NS32K 97
#define EM_TPC 98
#define EM_SNP1K 99
#define EM_ST200 100
#define EM_IP2K 101
#define EM_MAX 102
#define EM_CR 103

#define EM_F2MC16 104
#define EM_MSP430 105

#define EM_BLACKFIN 106
#define EM_SE_C33 107
#define EM_SEP 108
#define EM_ARCA 109
#define EM_UNICORE 110

#define EM_486 6
#define EM_MIPS_RS4_BE 10
#define EM_ALPHA_STD 41
#define EM_ALPHA 0x9026

#define SHN_UNDEF 0
#define SHN_LORESERVE 0xff00
#define SHN_LOPROC 0xff00
#define SHN_HIPROC 0xff1f
#define SHN_LOOS 0xff20
#define SHN_HIOS 0xff3f
#define SHN_ABS 0xfff1
#define SHN_COMMON 0xfff2
#define SHN_XINDEX 0xffff
#define SHN_HIRESERVE 0xffff

#define SHT_NULL 0
#define SHT_PROGBITS 1
#define SHT_SYMTAB 2
#define SHT_STRTAB 3
#define SHT_RELA 4
#define SHT_HASH 5
#define SHT_DYNAMIC 6
#define SHT_NOTE 7
#define SHT_NOBITS 8
#define SHT_REL 9
#define SHT_SHLIB 10
#define SHT_DYNSYM 11
#define SHT_INIT_ARRAY 14
#define SHT_FINI_ARRAY 15
#define SHT_PREINIT_ARRAY 16
#define SHT_GROUP 17
#define SHT_SYMTAB_SHNDX 18
#define SHT_LOOS 0x60000000
#define SHT_LOSUNW 0x6ffffff4
#define SHT_SUNW_dof 0x6ffffff4
#define SHT_SUNW_cap 0x6ffffff5
#define SHT_SUNW_SIGNATURE 0x6ffffff6
#define SHT_GNU_HASH 0x6ffffff6
#define SHT_SUNW_ANNOTATE 0x6ffffff7
#define SHT_SUNW_DEBUGSTR 0x6ffffff8
#define SHT_SUNW_DEBUG 0x6ffffff9
#define SHT_SUNW_move 0x6ffffffa
#define SHT_SUNW_COMDAT 0x6ffffffb
#define SHT_SUNW_syminfo 0x6ffffffc
#define SHT_SUNW_verdef 0x6ffffffd
#define SHT_GNU_verdef 0x6ffffffd
#define SHT_SUNW_verneed 0x6ffffffe
#define SHT_GNU_verneed 0x6ffffffe
#define SHT_SUNW_versym 0x6fffffff
#define SHT_GNU_versym 0x6fffffff
#define SHT_HISUNW 0x6fffffff
#define SHT_HIOS 0x6fffffff
#define SHT_LOPROC 0x70000000
#define SHT_AMD64_UNWIND 0x70000001
#define SHT_MIPS_DWARF 0x7000001e
#define SHT_HIPROC 0x7fffffff
#define SHT_LOUSER 0x80000000
#define SHT_HIUSER 0xffffffff

#define SHF_WRITE 0x1
#define SHF_ALLOC 0x2
#define SHF_EXECINSTR 0x4
#define SHF_MERGE 0x10
#define SHF_STRINGS 0x20
#define SHF_INFO_LINK 0x40
#define SHF_LINK_ORDER 0x80
#define SHF_OS_NONCONFORMING 0x100
#define SHF_GROUP 0x200
#define SHF_TLS 0x400
#define SHF_MASKOS 0x0ff00000
#define SHF_MASKPROC 0xf0000000

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2
#define PT_INTERP 3
#define PT_NOTE 4
#define PT_SHLIB 5
#define PT_PHDR 6
#define PT_TLS 7
#define PT_LOOS 0x60000000
#define PT_SUNW_UNWIND 0x6464e550
#define PT_GNU_EH_FRAME 0x6474e550
#define PT_GNU_STACK 0x6474e551
#define PT_LOSUNW 0x6ffffffa
#define PT_SUNWBSS 0x6ffffffa
#define PT_SUNWSTACK 0x6ffffffb
#define PT_SUNWDTRACE 0x6ffffffc
#define PT_SUNWCAP 0x6ffffffd
#define PT_HISUNW 0x6fffffff
#define PT_HIOS 0x6fffffff
#define PT_LOPROC 0x70000000
#define PT_HIPROC 0x7fffffff

#define PF_X 0x1
#define PF_W 0x2
#define PF_R 0x4
#define PF_MASKOS 0x0ff00000
#define PF_MASKPROC 0xf0000000

#define PN_XNUM 0xffff

#define DT_NULL 0
#define DT_NEEDED 1

#define DT_PLTRELSZ 2
#define DT_PLTGOT 3
#define DT_HASH 4
#define DT_STRTAB 5
#define DT_SYMTAB 6
#define DT_RELA 7
#define DT_RELASZ 8
#define DT_RELAENT 9
#define DT_STRSZ 10
#define DT_SYMENT 11
#define DT_INIT 12
#define DT_FINI 13
#define DT_SONAME 14

#define DT_RPATH 15
#define DT_SYMBOLIC 16
#define DT_REL 17
#define DT_RELSZ 18
#define DT_RELENT 19
#define DT_PLTREL 20
#define DT_DEBUG 21
#define DT_TEXTREL 22

#define DT_JMPREL 23
#define DT_BIND_NOW 24
#define DT_INIT_ARRAY 25

#define DT_FINI_ARRAY 26

#define DT_INIT_ARRAYSZ 27

#define DT_FINI_ARRAYSZ 28

#define DT_RUNPATH 29

#define DT_FLAGS 30
#define DT_ENCODING 32

#define DT_PREINIT_ARRAY 32

#define DT_PREINIT_ARRAYSZ 33

#define DT_MAXPOSTAGS 34
#define DT_LOOS 0x6000000d
#define DT_SUNW_AUXILIARY 0x6000000d
#define DT_SUNW_RTLDINF 0x6000000e
#define DT_SUNW_FILTER 0x6000000f
#define DT_SUNW_CAP 0x60000010
#define DT_HIOS 0x6ffff000

#define DT_VALRNGLO 0x6ffffd00
#define DT_CHECKSUM 0x6ffffdf8
#define DT_PLTPADSZ 0x6ffffdf9
#define DT_MOVEENT 0x6ffffdfa
#define DT_MOVESZ 0x6ffffdfb
#define DT_FEATURE_1 0x6ffffdfc
#define DT_POSFLAG_1 0x6ffffdfd

#define DT_SYMINSZ 0x6ffffdfe
#define DT_SYMINENT 0x6ffffdff
#define DT_VALRNGHI 0x6ffffdff

#define DT_ADDRRNGLO 0x6ffffe00
#define DT_GNU_HASH 0x6ffffef5
#define DT_CONFIG 0x6ffffefa
#define DT_DEPAUDIT 0x6ffffefb
#define DT_AUDIT 0x6ffffefc
#define DT_PLTPAD 0x6ffffefd
#define DT_MOVETAB 0x6ffffefe
#define DT_SYMINFO 0x6ffffeff
#define DT_ADDRRNGHI 0x6ffffeff

#define DT_VERSYM 0x6ffffff0
#define DT_RELACOUNT 0x6ffffff9
#define DT_RELCOUNT 0x6ffffffa
#define DT_FLAGS_1 0x6ffffffb
#define DT_VERDEF 0x6ffffffc
#define DT_VERDEFNUM 0x6ffffffd
#define DT_VERNEED 0x6ffffffe
#define DT_VERNEEDNUM 0x6fffffff

#define DT_LOPROC 0x70000000
#define DT_DEPRECATED_SPARC_REGISTER 0x7000001
#define DT_AUXILIARY 0x7ffffffd
#define DT_USED 0x7ffffffe
#define DT_FILTER 0x7fffffff
#define DT_HIPROC 0x7fffffff

#define DF_ORIGIN 0x0001

#define DF_SYMBOLIC 0x0002
#define DF_TEXTREL 0x0004

#define DF_BIND_NOW 0x0008

#define DF_STATIC_TLS 0x0010

#define DF_1_BIND_NOW 0x00000001
#define DF_1_GLOBAL 0x00000002
#define DF_1_NODELETE 0x00000008
#define DF_1_LOADFLTR 0x00000010
#define DF_1_NOOPEN 0x00000040
#define DF_1_ORIGIN 0x00000080

#define NT_PRSTATUS 1
#define NT_FPREGSET 2
#define NT_PRPSINFO 3
#define NT_THRMISC 7

#define STB_LOCAL 0
#define STB_GLOBAL 1
#define STB_WEAK 2
#define STB_LOOS 10
#define STB_HIOS 12
#define STB_LOPROC 13
#define STB_HIPROC 15

#define STT_NOTYPE 0
#define STT_OBJECT 1
#define STT_FUNC 2
#define STT_SECTION 3
#define STT_FILE 4
#define STT_COMMON 5
#define STT_TLS 6
#define STT_NUM 7
#define STT_LOOS 10
#define STT_HIOS 12
#define STT_LOPROC 13
#define STT_HIPROC 15

#define STV_DEFAULT 0x0
#define STV_INTERNAL 0x1
#define STV_HIDDEN 0x2
#define STV_PROTECTED 0x3
#define STV_EXPORTED 0x4
#define STV_SINGLETON 0x5
#define STV_ELIMINATE 0x6

#define STN_UNDEF 0

#define VER_DEF_CURRENT 1
#define VER_DEF_IDX(x) VER_NDX(x)

#define VER_FLG_BASE 0x01
#define VER_FLG_WEAK 0x02

#define VER_NEED_CURRENT 1
#define VER_NEED_WEAK (1u << 15)
#define VER_NEED_HIDDEN VER_NDX_HIDDEN
#define VER_NEED_IDX(x) VER_NDX(x)

#define VER_NDX_LOCAL 0
#define VER_NDX_GLOBAL 1
#define VER_NDX_GIVEN 2

#define VER_NDX_HIDDEN (1u << 15)
#define VER_NDX(x) ((x) & ~(1u << 15))

#define CA_SUNW_NULL 0
#define CA_SUNW_HW_1 1
#define CA_SUNW_SF_1 2

#define SYMINFO_FLG_DIRECT 0x0001

#define SYMINFO_FLG_PASSTHRU 0x0002
#define SYMINFO_FLG_COPY 0x0004
#define SYMINFO_FLG_LAZYLOAD 0x0008

#define SYMINFO_FLG_DIRECTBIND 0x0010

#define SYMINFO_FLG_NOEXTDIRECT 0x0020

#define SYMINFO_FLG_FILTER 0x0002
#define SYMINFO_FLG_AUXILIARY 0x0040

#define SYMINFO_BT_SELF 0xffff
#define SYMINFO_BT_PARENT 0xfffe
#define SYMINFO_BT_NONE 0xfffd
#define SYMINFO_BT_EXTERN 0xfffc
#define SYMINFO_BT_LOWRESERVE 0xff00

#define SYMINFO_NONE 0
#define SYMINFO_CURRENT 1
#define SYMINFO_NUM 2

#define R_386_NONE 0
#define R_386_32 1
#define R_386_PC32 2
#define R_386_GOT32 3
#define R_386_PLT32 4
#define R_386_COPY 5
#define R_386_GLOB_DAT 6
#define R_386_JMP_SLOT 7
#define R_386_RELATIVE 8
#define R_386_GOTOFF 9
#define R_386_GOTPC 10
#define R_386_TLS_TPOFF 14
#define R_386_TLS_IE 15
#define R_386_TLS_GOTIE 16
#define R_386_TLS_LE 17
#define R_386_TLS_GD 18
#define R_386_TLS_LDM 19
#define R_386_TLS_GD_32 24
#define R_386_TLS_GD_PUSH 25
#define R_386_TLS_GD_CALL 26
#define R_386_TLS_GD_POP 27
#define R_386_TLS_LDM_32 28
#define R_386_TLS_LDM_PUSH 29
#define R_386_TLS_LDM_CALL 30
#define R_386_TLS_LDM_POP 31
#define R_386_TLS_LDO_32 32
#define R_386_TLS_IE_32 33
#define R_386_TLS_LE_32 34
#define R_386_TLS_DTPMOD32 35
#define R_386_TLS_DTPOFF32 36
#define R_386_TLS_TPOFF32 37

#define R_ARM_NONE 0
#define R_ARM_PC24 1
#define R_ARM_ABS32 2
#define R_ARM_REL32 3
#define R_ARM_PC13 4
#define R_ARM_ABS16 5
#define R_ARM_ABS12 6
#define R_ARM_THM_ABS5 7
#define R_ARM_ABS8 8
#define R_ARM_SBREL32 9
#define R_ARM_THM_PC22 10
#define R_ARM_THM_PC8 11
#define R_ARM_AMP_VCALL9 12
#define R_ARM_SWI24 13
#define R_ARM_THM_SWI8 14
#define R_ARM_XPC25 15
#define R_ARM_THM_XPC22 16
#define R_ARM_COPY 20
#define R_ARM_GLOB_DAT 21
#define R_ARM_JUMP_SLOT 22
#define R_ARM_RELATIVE 23
#define R_ARM_GOTOFF 24
#define R_ARM_GOTPC 25
#define R_ARM_GOT32 26
#define R_ARM_PLT32 27
#define R_ARM_GNU_VTENTRY 100
#define R_ARM_GNU_VTINHERIT 101
#define R_ARM_RSBREL32 250
#define R_ARM_THM_RPC22 251
#define R_ARM_RREL32 252
#define R_ARM_RABS32 253
#define R_ARM_RPC24 254
#define R_ARM_RBASE 255

#define R_IA_64_NONE 0
#define R_IA_64_IMM14 0x21
#define R_IA_64_IMM22 0x22
#define R_IA_64_IMM64 0x23
#define R_IA_64_DIR32MSB 0x24
#define R_IA_64_DIR32LSB 0x25
#define R_IA_64_DIR64MSB 0x26
#define R_IA_64_DIR64LSB 0x27
#define R_IA_64_GPREL22 0x2a
#define R_IA_64_GPREL64I 0x2b
#define R_IA_64_GPREL32MSB 0x2c
#define R_IA_64_GPREL32LSB 0x2d
#define R_IA_64_GPREL64MSB 0x2e
#define R_IA_64_GPREL64LSB 0x2f
#define R_IA_64_LTOFF22 0x32
#define R_IA_64_LTOFF64I 0x33
#define R_IA_64_PLTOFF22 0x3a
#define R_IA_64_PLTOFF64I 0x3b
#define R_IA_64_PLTOFF64MSB 0x3e
#define R_IA_64_PLTOFF64LSB 0x3f
#define R_IA_64_FPTR64I 0x43
#define R_IA_64_FPTR32MSB 0x44
#define R_IA_64_FPTR32LSB 0x45
#define R_IA_64_FPTR64MSB 0x46
#define R_IA_64_FPTR64LSB 0x47
#define R_IA_64_PCREL60B 0x48
#define R_IA_64_PCREL21B 0x49
#define R_IA_64_PCREL21M 0x4a
#define R_IA_64_PCREL21F 0x4b
#define R_IA_64_PCREL32MSB 0x4c
#define R_IA_64_PCREL32LSB 0x4d
#define R_IA_64_PCREL64MSB 0x4e
#define R_IA_64_PCREL64LSB 0x4f
#define R_IA_64_LTOFF_FPTR22 0x52
#define R_IA_64_LTOFF_FPTR64I 0x53
#define R_IA_64_LTOFF_FPTR32MSB 0x54
#define R_IA_64_LTOFF_FPTR32LSB 0x55
#define R_IA_64_LTOFF_FPTR64MSB 0x56
#define R_IA_64_LTOFF_FPTR64LSB 0x57
#define R_IA_64_SEGREL32MSB 0x5c
#define R_IA_64_SEGREL32LSB 0x5d
#define R_IA_64_SEGREL64MSB 0x5e
#define R_IA_64_SEGREL64LSB 0x5f
#define R_IA_64_SECREL32MSB 0x64
#define R_IA_64_SECREL32LSB 0x65
#define R_IA_64_SECREL64MSB 0x66
#define R_IA_64_SECREL64LSB 0x67
#define R_IA_64_REL32MSB 0x6c
#define R_IA_64_REL32LSB 0x6d
#define R_IA_64_REL64MSB 0x6e
#define R_IA_64_REL64LSB 0x6f
#define R_IA_64_LTV32MSB 0x74
#define R_IA_64_LTV32LSB 0x75
#define R_IA_64_LTV64MSB 0x76
#define R_IA_64_LTV64LSB 0x77
#define R_IA_64_PCREL21BI 0x79
#define R_IA_64_PCREL22 0x7a
#define R_IA_64_PCREL64I 0x7b
#define R_IA_64_IPLTMSB 0x80
#define R_IA_64_IPLTLSB 0x81
#define R_IA_64_SUB 0x85
#define R_IA_64_LTOFF22X 0x86
#define R_IA_64_LDXMOV 0x87
#define R_IA_64_TPREL14 0x91
#define R_IA_64_TPREL22 0x92
#define R_IA_64_TPREL64I 0x93
#define R_IA_64_TPREL64MSB 0x96
#define R_IA_64_TPREL64LSB 0x97
#define R_IA_64_LTOFF_TPREL22 0x9a
#define R_IA_64_DTPMOD64MSB 0xa6
#define R_IA_64_DTPMOD64LSB 0xa7
#define R_IA_64_LTOFF_DTPMOD22 0xaa
#define R_IA_64_DTPREL14 0xb1
#define R_IA_64_DTPREL22 0xb2
#define R_IA_64_DTPREL64I 0xb3
#define R_IA_64_DTPREL32MSB 0xb4
#define R_IA_64_DTPREL32LSB 0xb5
#define R_IA_64_DTPREL64MSB 0xb6
#define R_IA_64_DTPREL64LSB 0xb7
#define R_IA_64_LTOFF_DTPREL22 0xba

#define R_MIPS_NONE 0
#define R_MIPS_16 1
#define R_MIPS_32 2
#define R_MIPS_REL32 3
#define R_MIPS_26 4
#define R_MIPS_HI16 5
#define R_MIPS_LO16 6
#define R_MIPS_GPREL16 7
#define R_MIPS_LITERAL 8
#define R_MIPS_GOT16 9
#define R_MIPS_PC16 10
#define R_MIPS_CALL16 11
#define R_MIPS_GPREL32 12
#define R_MIPS_GOTHI16 21
#define R_MIPS_GOTLO16 22
#define R_MIPS_CALLHI16 30
#define R_MIPS_CALLLO16 31

#define R_PPC_NONE 0
#define R_PPC_ADDR32 1
#define R_PPC_ADDR24 2
#define R_PPC_ADDR16 3
#define R_PPC_ADDR16_LO 4
#define R_PPC_ADDR16_HI 5
#define R_PPC_ADDR16_HA 6
#define R_PPC_ADDR14 7
#define R_PPC_ADDR14_BRTAKEN 8
#define R_PPC_ADDR14_BRNTAKEN 9
#define R_PPC_REL24 10
#define R_PPC_REL14 11
#define R_PPC_REL14_BRTAKEN 12
#define R_PPC_REL14_BRNTAKEN 13
#define R_PPC_GOT16 14
#define R_PPC_GOT16_LO 15
#define R_PPC_GOT16_HI 16
#define R_PPC_GOT16_HA 17
#define R_PPC_PLTREL24 18
#define R_PPC_COPY 19
#define R_PPC_GLOB_DAT 20
#define R_PPC_JMP_SLOT 21
#define R_PPC_RELATIVE 22
#define R_PPC_LOCAL24PC 23
#define R_PPC_UADDR32 24
#define R_PPC_UADDR16 25
#define R_PPC_REL32 26
#define R_PPC_PLT32 27
#define R_PPC_PLTREL32 28
#define R_PPC_PLT16_LO 29
#define R_PPC_PLT16_HI 30
#define R_PPC_PLT16_HA 31
#define R_PPC_SDAREL16 32
#define R_PPC_SECTOFF 33
#define R_PPC_SECTOFF_LO 34
#define R_PPC_SECTOFF_HI 35
#define R_PPC_SECTOFF_HA 36

#define R_PPC64_ADDR64 38
#define R_PPC64_ADDR16_HIGHER 39
#define R_PPC64_ADDR16_HIGHERA 40
#define R_PPC64_ADDR16_HIGHEST 41
#define R_PPC64_ADDR16_HIGHESTA 42
#define R_PPC64_UADDR64 43
#define R_PPC64_REL64 44
#define R_PPC64_PLT64 45
#define R_PPC64_PLTREL64 46
#define R_PPC64_TOC16 47
#define R_PPC64_TOC16_LO 48
#define R_PPC64_TOC16_HI 49
#define R_PPC64_TOC16_HA 50
#define R_PPC64_TOC 51
#define R_PPC64_DTPMOD64 68
#define R_PPC64_TPREL64 73
#define R_PPC64_DTPREL64 78

#define R_PPC_TLS 67
#define R_PPC_DTPMOD32 68
#define R_PPC_TPREL16 69
#define R_PPC_TPREL16_LO 70
#define R_PPC_TPREL16_HI 71
#define R_PPC_TPREL16_HA 72
#define R_PPC_TPREL32 73
#define R_PPC_DTPREL16 74
#define R_PPC_DTPREL16_LO 75
#define R_PPC_DTPREL16_HI 76
#define R_PPC_DTPREL16_HA 77
#define R_PPC_DTPREL32 78
#define R_PPC_GOT_TLSGD16 79
#define R_PPC_GOT_TLSGD16_LO 80
#define R_PPC_GOT_TLSGD16_HI 81
#define R_PPC_GOT_TLSGD16_HA 82
#define R_PPC_GOT_TLSLD16 83
#define R_PPC_GOT_TLSLD16_LO 84
#define R_PPC_GOT_TLSLD16_HI 85
#define R_PPC_GOT_TLSLD16_HA 86
#define R_PPC_GOT_TPREL16 87
#define R_PPC_GOT_TPREL16_LO 88
#define R_PPC_GOT_TPREL16_HI 89
#define R_PPC_GOT_TPREL16_HA 90

#define R_PPC_EMB_NADDR32 101
#define R_PPC_EMB_NADDR16 102
#define R_PPC_EMB_NADDR16_LO 103
#define R_PPC_EMB_NADDR16_HI 104
#define R_PPC_EMB_NADDR16_HA 105
#define R_PPC_EMB_SDAI16 106
#define R_PPC_EMB_SDA2I16 107
#define R_PPC_EMB_SDA2REL 108
#define R_PPC_EMB_SDA21 109
#define R_PPC_EMB_MRKREF 110
#define R_PPC_EMB_RELSEC16 111
#define R_PPC_EMB_RELST_LO 112
#define R_PPC_EMB_RELST_HI 113
#define R_PPC_EMB_RELST_HA 114
#define R_PPC_EMB_BIT_FLD 115
#define R_PPC_EMB_RELSDA 116

#define R_SPARC_NONE 0
#define R_SPARC_8 1
#define R_SPARC_16 2
#define R_SPARC_32 3
#define R_SPARC_DISP8 4
#define R_SPARC_DISP16 5
#define R_SPARC_DISP32 6
#define R_SPARC_WDISP30 7
#define R_SPARC_WDISP22 8
#define R_SPARC_HI22 9
#define R_SPARC_22 10
#define R_SPARC_13 11
#define R_SPARC_LO10 12
#define R_SPARC_GOT10 13
#define R_SPARC_GOT13 14
#define R_SPARC_GOT22 15
#define R_SPARC_PC10 16
#define R_SPARC_PC22 17
#define R_SPARC_WPLT30 18
#define R_SPARC_COPY 19
#define R_SPARC_GLOB_DAT 20
#define R_SPARC_JMP_SLOT 21
#define R_SPARC_RELATIVE 22
#define R_SPARC_UA32 23
#define R_SPARC_PLT32 24
#define R_SPARC_HIPLT22 25
#define R_SPARC_LOPLT10 26
#define R_SPARC_PCPLT32 27
#define R_SPARC_PCPLT22 28
#define R_SPARC_PCPLT10 29
#define R_SPARC_10 30
#define R_SPARC_11 31
#define R_SPARC_64 32
#define R_SPARC_OLO10 33
#define R_SPARC_HH22 34
#define R_SPARC_HM10 35
#define R_SPARC_LM22 36
#define R_SPARC_PC_HH22 37
#define R_SPARC_PC_HM10 38
#define R_SPARC_PC_LM22 39
#define R_SPARC_WDISP16 40
#define R_SPARC_WDISP19 41
#define R_SPARC_GLOB_JMP 42
#define R_SPARC_7 43
#define R_SPARC_5 44
#define R_SPARC_6 45
#define R_SPARC_DISP64 46
#define R_SPARC_PLT64 47
#define R_SPARC_HIX22 48
#define R_SPARC_LOX10 49
#define R_SPARC_H44 50
#define R_SPARC_M44 51
#define R_SPARC_L44 52
#define R_SPARC_REGISTER 53
#define R_SPARC_UA64 54
#define R_SPARC_UA16 55
#define R_SPARC_TLS_GD_HI22 56
#define R_SPARC_TLS_GD_LO10 57
#define R_SPARC_TLS_GD_ADD 58
#define R_SPARC_TLS_GD_CALL 59
#define R_SPARC_TLS_LDM_HI22 60
#define R_SPARC_TLS_LDM_LO10 61
#define R_SPARC_TLS_LDM_ADD 62
#define R_SPARC_TLS_LDM_CALL 63
#define R_SPARC_TLS_LDO_HIX22 64
#define R_SPARC_TLS_LDO_LOX10 65
#define R_SPARC_TLS_LDO_ADD 66
#define R_SPARC_TLS_IE_HI22 67
#define R_SPARC_TLS_IE_LO10 68
#define R_SPARC_TLS_IE_LD 69
#define R_SPARC_TLS_IE_LDX 70
#define R_SPARC_TLS_IE_ADD 71
#define R_SPARC_TLS_LE_HIX22 72
#define R_SPARC_TLS_LE_LOX10 73
#define R_SPARC_TLS_DTPMOD32 74
#define R_SPARC_TLS_DTPMOD64 75
#define R_SPARC_TLS_DTPOFF32 76
#define R_SPARC_TLS_DTPOFF64 77
#define R_SPARC_TLS_TPOFF32 78
#define R_SPARC_TLS_TPOFF64 79

#define R_X86_64_NONE 0
#define R_X86_64_64 1
#define R_X86_64_PC32 2
#define R_X86_64_GOT32 3
#define R_X86_64_PLT32 4
#define R_X86_64_COPY 5
#define R_X86_64_GLOB_DAT 6
#define R_X86_64_JMP_SLOT 7
#define R_X86_64_RELATIVE 8
#define R_X86_64_GOTPCREL 9
#define R_X86_64_32 10
#define R_X86_64_32S 11
#define R_X86_64_16 12
#define R_X86_64_PC16 13
#define R_X86_64_8 14
#define R_X86_64_PC8 15
#define R_X86_64_DTPMOD64 16
#define R_X86_64_DTPOFF64 17
#define R_X86_64_TPOFF64 18
#define R_X86_64_TLSGD 19
#define R_X86_64_TLSLD 20
#define R_X86_64_DTPOFF32 21
#define R_X86_64_GOTTPOFF 22
#define R_X86_64_TPOFF32 23

#endif
