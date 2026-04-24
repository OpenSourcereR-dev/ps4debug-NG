
#ifndef _ELF_H
#define _ELF_H

#include <ksdk.h>

#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

#define ELF64_R_SYM(i)    ((i)>>32)
#define ELF64_R_TYPE(i)   ((i)&0xffffffffL)
#define ELF64_R_INFO(s,t) (((s)<<32)+((t)&0xffffffffL))

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;

typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;
typedef uint16_t Elf64_Half;
typedef uint32_t Elf64_Word;
typedef int32_t  Elf64_Sword;
typedef uint64_t Elf64_Xword;
typedef int64_t  Elf64_Sxword;

static const char ElfMagic[] = { 0x7f, 'E', 'L', 'F', '\0' };

enum {
    EI_MAG0       = 0,
    EI_MAG1       = 1,
    EI_MAG2       = 2,
    EI_MAG3       = 3,
    EI_CLASS      = 4,
    EI_DATA       = 5,
    EI_VERSION    = 6,
    EI_OSABI      = 7,
    EI_ABIVERSION = 8,
    EI_PAD        = 9,
    EI_NIDENT     = 16
};

struct Elf32_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half    e_type;
    Elf32_Half    e_machine;
    Elf32_Word    e_version;
    Elf32_Addr    e_entry;
    Elf32_Off     e_phoff;
    Elf32_Off     e_shoff;
    Elf32_Word    e_flags;
    Elf32_Half    e_ehsize;
    Elf32_Half    e_phentsize;
    Elf32_Half    e_phnum;
    Elf32_Half    e_shentsize;
    Elf32_Half    e_shnum;
    Elf32_Half    e_shstrndx;
};

struct Elf64_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf64_Half    e_type;
    Elf64_Half    e_machine;
    Elf64_Word    e_version;
    Elf64_Addr    e_entry;
    Elf64_Off     e_phoff;
    Elf64_Off     e_shoff;
    Elf64_Word    e_flags;
    Elf64_Half    e_ehsize;
    Elf64_Half    e_phentsize;
    Elf64_Half    e_phnum;
    Elf64_Half    e_shentsize;
    Elf64_Half    e_shnum;
    Elf64_Half    e_shstrndx;
};

enum {
    ET_NONE   = 0,
    ET_REL    = 1,
    ET_EXEC   = 2,
    ET_DYN    = 3,
    ET_CORE   = 4,
    ET_LOPROC = 0xff00,
    ET_HIPROC = 0xffff
};

enum {
    EV_NONE = 0,
    EV_CURRENT = 1
};

enum {
    EM_NONE          = 0,
    EM_M32           = 1,
    EM_SPARC         = 2,
    EM_386           = 3,
    EM_68K           = 4,
    EM_88K           = 5,
    EM_486           = 6,
    EM_860           = 7,
    EM_MIPS          = 8,
    EM_S370          = 9,
    EM_MIPS_RS3_LE   = 10,
    EM_PARISC        = 15,
    EM_VPP500        = 17,
    EM_SPARC32PLUS   = 18,
    EM_960           = 19,
    EM_PPC           = 20,
    EM_PPC64         = 21,
    EM_S390          = 22,
    EM_SPU           = 23,
    EM_V800          = 36,
    EM_FR20          = 37,
    EM_RH32          = 38,
    EM_RCE           = 39,
    EM_ARM           = 40,
    EM_ALPHA         = 41,
    EM_SH            = 42,
    EM_SPARCV9       = 43,
    EM_TRICORE       = 44,
    EM_ARC           = 45,
    EM_H8_300        = 46,
    EM_H8_300H       = 47,
    EM_H8S           = 48,
    EM_H8_500        = 49,
    EM_IA_64         = 50,
    EM_MIPS_X        = 51,
    EM_COLDFIRE      = 52,
    EM_68HC12        = 53,
    EM_MMA           = 54,
    EM_PCP           = 55,
    EM_NCPU          = 56,
    EM_NDR1          = 57,
    EM_STARCORE      = 58,
    EM_ME16          = 59,
    EM_ST100         = 60,
    EM_TINYJ         = 61,
    EM_X86_64        = 62,
    EM_PDSP          = 63,
    EM_PDP10         = 64,
    EM_PDP11         = 65,
    EM_FX66          = 66,
    EM_ST9PLUS       = 67,
    EM_ST7           = 68,
    EM_68HC16        = 69,
    EM_68HC11        = 70,
    EM_68HC08        = 71,
    EM_68HC05        = 72,
    EM_SVX           = 73,
    EM_ST19          = 74,
    EM_VAX           = 75,
    EM_CRIS          = 76,
    EM_JAVELIN       = 77,
    EM_FIREPATH      = 78,
    EM_ZSP           = 79,
    EM_MMIX          = 80,
    EM_HUANY         = 81,
    EM_PRISM         = 82,
    EM_AVR           = 83,
    EM_FR30          = 84,
    EM_D10V          = 85,
    EM_D30V          = 86,
    EM_V850          = 87,
    EM_M32R          = 88,
    EM_MN10300       = 89,
    EM_MN10200       = 90,
    EM_PJ            = 91,
    EM_OPENRISC      = 92,
    EM_ARC_COMPACT   = 93,

    EM_XTENSA        = 94,
    EM_VIDEOCORE     = 95,
    EM_TMM_GPP       = 96,
    EM_NS32K         = 97,
    EM_TPC           = 98,
    EM_SNP1K         = 99,
    EM_ST200         = 100,
    EM_IP2K          = 101,
    EM_MAX           = 102,
    EM_CR            = 103,
    EM_F2MC16        = 104,
    EM_MSP430        = 105,
    EM_BLACKFIN      = 106,
    EM_SE_C33        = 107,
    EM_SEP           = 108,
    EM_ARCA          = 109,
    EM_UNICORE       = 110,

    EM_EXCESS        = 111,
    EM_DXP           = 112,
    EM_ALTERA_NIOS2  = 113,
    EM_CRX           = 114,
    EM_XGATE         = 115,
    EM_C166          = 116,
    EM_M16C          = 117,
    EM_DSPIC30F      = 118,

    EM_CE            = 119,
    EM_M32C          = 120,
    EM_TSK3000       = 131,
    EM_RS08          = 132,
    EM_SHARC         = 133,

    EM_ECOG2         = 134,
    EM_SCORE7        = 135,
    EM_DSP24         = 136,
    EM_VIDEOCORE3    = 137,
    EM_LATTICEMICO32 = 138,
    EM_SE_C17        = 139,
    EM_TI_C6000      = 140,
    EM_TI_C2000      = 141,
    EM_TI_C5500      = 142,
    EM_MMDSP_PLUS    = 160,
    EM_CYPRESS_M8C   = 161,
    EM_R32C          = 162,
    EM_TRIMEDIA      = 163,
    EM_HEXAGON       = 164,
    EM_8051          = 165,
    EM_STXP7X        = 166,

    EM_NDS32         = 167,

    EM_ECOG1         = 168,
    EM_ECOG1X        = 168,
    EM_MAXQ30        = 169,
    EM_XIMO16        = 170,
    EM_MANIK         = 171,
    EM_CRAYNV2       = 172,
    EM_RX            = 173,
    EM_METAG         = 174,

    EM_MCST_ELBRUS   = 175,
    EM_ECOG16        = 176,
    EM_CR16          = 177,

    EM_ETPU          = 178,
    EM_SLE9X         = 179,
    EM_L10M          = 180,
    EM_K10M          = 181,
    EM_AARCH64       = 183,
    EM_AVR32         = 185,
    EM_STM8          = 186,
    EM_TILE64        = 187,
    EM_TILEPRO       = 188,
    EM_MICROBLAZE    = 189,
    EM_CUDA          = 190,
    EM_TILEGX        = 191,
    EM_CLOUDSHIELD   = 192,
    EM_COREA_1ST     = 193,
    EM_COREA_2ND     = 194,
    EM_ARC_COMPACT2  = 195,
    EM_OPEN8         = 196,
    EM_RL78          = 197,
    EM_VIDEOCORE5    = 198,
    EM_78KOR         = 199,
    EM_56800EX       = 200,
    EM_MBLAZE        = 47787
};

enum {
    ELFCLASSNONE = 0,
    ELFCLASS32 = 1,
    ELFCLASS64 = 2
};

enum {
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2
};

enum {
    ELFOSABI_NONE = 0,
    ELFOSABI_HPUX = 1,
    ELFOSABI_NETBSD = 2,
    ELFOSABI_LINUX = 3,
    ELFOSABI_HURD = 4,
    ELFOSABI_SOLARIS = 6,
    ELFOSABI_AIX = 7,
    ELFOSABI_IRIX = 8,
    ELFOSABI_FREEBSD = 9,
    ELFOSABI_TRU64 = 10,
    ELFOSABI_MODESTO = 11,
    ELFOSABI_OPENBSD = 12,
    ELFOSABI_OPENVMS = 13,
    ELFOSABI_NSK = 14,
    ELFOSABI_AROS = 15,
    ELFOSABI_FENIXOS = 16,
    ELFOSABI_C6000_ELFABI = 64,
    ELFOSABI_C6000_LINUX = 65,
    ELFOSABI_ARM = 97,
    ELFOSABI_STANDALONE = 255
};

enum {
    R_X86_64_NONE       = 0,
    R_X86_64_64         = 1,
    R_X86_64_PC32       = 2,
    R_X86_64_GOT32      = 3,
    R_X86_64_PLT32      = 4,
    R_X86_64_COPY       = 5,
    R_X86_64_GLOB_DAT   = 6,
    R_X86_64_JUMP_SLOT  = 7,
    R_X86_64_RELATIVE   = 8,
    R_X86_64_GOTPCREL   = 9,
    R_X86_64_32         = 10,
    R_X86_64_32S        = 11,
    R_X86_64_16         = 12,
    R_X86_64_PC16       = 13,
    R_X86_64_8          = 14,
    R_X86_64_PC8        = 15,
    R_X86_64_DTPMOD64   = 16,
    R_X86_64_DTPOFF64   = 17,
    R_X86_64_TPOFF64    = 18,
    R_X86_64_TLSGD      = 19,
    R_X86_64_TLSLD      = 20,
    R_X86_64_DTPOFF32   = 21,
    R_X86_64_GOTTPOFF   = 22,
    R_X86_64_TPOFF32    = 23,
    R_X86_64_PC64       = 24,
    R_X86_64_GOTOFF64   = 25,
    R_X86_64_GOTPC32    = 26,
    R_X86_64_GOT64      = 27,
    R_X86_64_GOTPCREL64 = 28,
    R_X86_64_GOTPC64    = 29,
    R_X86_64_GOTPLT64   = 30,
    R_X86_64_PLTOFF64   = 31,
    R_X86_64_SIZE32     = 32,
    R_X86_64_SIZE64     = 33,
    R_X86_64_GOTPC32_TLSDESC = 34,
    R_X86_64_TLSDESC_CALL    = 35,
    R_X86_64_TLSDESC    = 36,
    R_X86_64_IRELATIVE  = 37
};

enum {
    R_386_NONE          = 0,
    R_386_32            = 1,
    R_386_PC32          = 2,
    R_386_GOT32         = 3,
    R_386_PLT32         = 4,
    R_386_COPY          = 5,
    R_386_GLOB_DAT      = 6,
    R_386_JUMP_SLOT     = 7,
    R_386_RELATIVE      = 8,
    R_386_GOTOFF        = 9,
    R_386_GOTPC         = 10,
    R_386_32PLT         = 11,
    R_386_TLS_TPOFF     = 14,
    R_386_TLS_IE        = 15,
    R_386_TLS_GOTIE     = 16,
    R_386_TLS_LE        = 17,
    R_386_TLS_GD        = 18,
    R_386_TLS_LDM       = 19,
    R_386_16            = 20,
    R_386_PC16          = 21,
    R_386_8             = 22,
    R_386_PC8           = 23,
    R_386_TLS_GD_32     = 24,
    R_386_TLS_GD_PUSH   = 25,
    R_386_TLS_GD_CALL   = 26,
    R_386_TLS_GD_POP    = 27,
    R_386_TLS_LDM_32    = 28,
    R_386_TLS_LDM_PUSH  = 29,
    R_386_TLS_LDM_CALL  = 30,
    R_386_TLS_LDM_POP   = 31,
    R_386_TLS_LDO_32    = 32,
    R_386_TLS_IE_32     = 33,
    R_386_TLS_LE_32     = 34,
    R_386_TLS_DTPMOD32  = 35,
    R_386_TLS_DTPOFF32  = 36,
    R_386_TLS_TPOFF32   = 37,
    R_386_TLS_GOTDESC   = 39,
    R_386_TLS_DESC_CALL = 40,
    R_386_TLS_DESC      = 41,
    R_386_IRELATIVE     = 42,
    R_386_NUM           = 43
};

enum {
    R_MICROBLAZE_NONE           = 0,
    R_MICROBLAZE_32             = 1,
    R_MICROBLAZE_32_PCREL       = 2,
    R_MICROBLAZE_64_PCREL       = 3,
    R_MICROBLAZE_32_PCREL_LO    = 4,
    R_MICROBLAZE_64             = 5,
    R_MICROBLAZE_32_LO          = 6,
    R_MICROBLAZE_SRO32          = 7,
    R_MICROBLAZE_SRW32          = 8,
    R_MICROBLAZE_64_NONE        = 9,
    R_MICROBLAZE_32_SYM_OP_SYM  = 10,
    R_MICROBLAZE_GNU_VTINHERIT  = 11,
    R_MICROBLAZE_GNU_VTENTRY    = 12,
    R_MICROBLAZE_GOTPC_64       = 13,
    R_MICROBLAZE_GOT_64         = 14,
    R_MICROBLAZE_PLT_64         = 15,
    R_MICROBLAZE_REL            = 16,
    R_MICROBLAZE_JUMP_SLOT      = 17,
    R_MICROBLAZE_GLOB_DAT       = 18,
    R_MICROBLAZE_GOTOFF_64      = 19,
    R_MICROBLAZE_GOTOFF_32      = 20,
    R_MICROBLAZE_COPY           = 21
};

enum {
    R_PPC_NONE                  = 0,
    R_PPC_ADDR32                = 1,
    R_PPC_ADDR24                = 2,
    R_PPC_ADDR16                = 3,
    R_PPC_ADDR16_LO             = 4,
    R_PPC_ADDR16_HI             = 5,
    R_PPC_ADDR16_HA             = 6,
    R_PPC_ADDR14                = 7,
    R_PPC_ADDR14_BRTAKEN        = 8,
    R_PPC_ADDR14_BRNTAKEN       = 9,
    R_PPC_REL24                 = 10,
    R_PPC_REL14                 = 11,
    R_PPC_REL14_BRTAKEN         = 12,
    R_PPC_REL14_BRNTAKEN        = 13,
    R_PPC_REL32                 = 26,
    R_PPC_TPREL16_LO            = 70,
    R_PPC_TPREL16_HA            = 72
};

enum {
    R_PPC64_NONE                = 0,
    R_PPC64_ADDR32              = 1,
    R_PPC64_ADDR16_LO           = 4,
    R_PPC64_ADDR16_HI           = 5,
    R_PPC64_ADDR14              = 7,
    R_PPC64_REL24               = 10,
    R_PPC64_REL32               = 26,
    R_PPC64_ADDR64              = 38,
    R_PPC64_ADDR16_HIGHER       = 39,
    R_PPC64_ADDR16_HIGHEST      = 41,
    R_PPC64_REL64               = 44,
    R_PPC64_TOC16               = 47,
    R_PPC64_TOC16_LO            = 48,
    R_PPC64_TOC16_HA            = 50,
    R_PPC64_TOC                 = 51,
    R_PPC64_ADDR16_DS           = 56,
    R_PPC64_ADDR16_LO_DS        = 57,
    R_PPC64_TOC16_DS            = 63,
    R_PPC64_TOC16_LO_DS         = 64,
    R_PPC64_TLS                 = 67,
    R_PPC64_TPREL16_LO          = 70,
    R_PPC64_TPREL16_HA          = 72,
    R_PPC64_DTPREL16_LO         = 75,
    R_PPC64_DTPREL16_HA         = 77,
    R_PPC64_GOT_TLSGD16_LO      = 80,
    R_PPC64_GOT_TLSGD16_HA      = 82,
    R_PPC64_GOT_TLSLD16_LO      = 84,
    R_PPC64_GOT_TLSLD16_HA      = 86,
    R_PPC64_GOT_TPREL16_LO_DS   = 88,
    R_PPC64_GOT_TPREL16_HA      = 90,
    R_PPC64_TLSGD               = 107,
    R_PPC64_TLSLD               = 108
};

enum {
    R_AARCH64_NONE                        = 0x100,

    R_AARCH64_ABS64                       = 0x101,
    R_AARCH64_ABS32                       = 0x102,
    R_AARCH64_ABS16                       = 0x103,
    R_AARCH64_PREL64                      = 0x104,
    R_AARCH64_PREL32                      = 0x105,
    R_AARCH64_PREL16                      = 0x106,

    R_AARCH64_MOVW_UABS_G0                = 0x107,
    R_AARCH64_MOVW_UABS_G0_NC             = 0x108,
    R_AARCH64_MOVW_UABS_G1                = 0x109,
    R_AARCH64_MOVW_UABS_G1_NC             = 0x10a,
    R_AARCH64_MOVW_UABS_G2                = 0x10b,
    R_AARCH64_MOVW_UABS_G2_NC             = 0x10c,
    R_AARCH64_MOVW_UABS_G3                = 0x10d,
    R_AARCH64_MOVW_SABS_G0                = 0x10e,
    R_AARCH64_MOVW_SABS_G1                = 0x10f,
    R_AARCH64_MOVW_SABS_G2                = 0x110,

    R_AARCH64_LD_PREL_LO19                = 0x111,
    R_AARCH64_ADR_PREL_LO21               = 0x112,
    R_AARCH64_ADR_PREL_PG_HI21            = 0x113,
    R_AARCH64_ADD_ABS_LO12_NC             = 0x115,
    R_AARCH64_LDST8_ABS_LO12_NC           = 0x116,

    R_AARCH64_TSTBR14                     = 0x117,
    R_AARCH64_CONDBR19                    = 0x118,
    R_AARCH64_JUMP26                      = 0x11a,
    R_AARCH64_CALL26                      = 0x11b,

    R_AARCH64_LDST16_ABS_LO12_NC          = 0x11c,
    R_AARCH64_LDST32_ABS_LO12_NC          = 0x11d,
    R_AARCH64_LDST64_ABS_LO12_NC          = 0x11e,

    R_AARCH64_LDST128_ABS_LO12_NC         = 0x12b,

    R_AARCH64_ADR_GOT_PAGE                = 0x137,
    R_AARCH64_LD64_GOT_LO12_NC            = 0x138,

    R_AARCH64_TLSLD_MOVW_DTPREL_G2        = 0x20b,
    R_AARCH64_TLSLD_MOVW_DTPREL_G1        = 0x20c,
    R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC     = 0x20d,
    R_AARCH64_TLSLD_MOVW_DTPREL_G0        = 0x20e,
    R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC     = 0x20f,
    R_AARCH64_TLSLD_ADD_DTPREL_HI12       = 0x210,
    R_AARCH64_TLSLD_ADD_DTPREL_LO12       = 0x211,
    R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC    = 0x212,
    R_AARCH64_TLSLD_LDST8_DTPREL_LO12     = 0x213,
    R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC  = 0x214,
    R_AARCH64_TLSLD_LDST16_DTPREL_LO12    = 0x215,
    R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC = 0x216,
    R_AARCH64_TLSLD_LDST32_DTPREL_LO12    = 0x217,
    R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC = 0x218,
    R_AARCH64_TLSLD_LDST64_DTPREL_LO12    = 0x219,
    R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC = 0x21a,

    R_AARCH64_TLSIE_MOVW_GOTTPREL_G1      = 0x21b,
    R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC   = 0x21c,
    R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21   = 0x21d,
    R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC = 0x21e,
    R_AARCH64_TLSIE_LD_GOTTPREL_PREL19    = 0x21f,

    R_AARCH64_TLSLE_MOVW_TPREL_G2         = 0x220,
    R_AARCH64_TLSLE_MOVW_TPREL_G1         = 0x221,
    R_AARCH64_TLSLE_MOVW_TPREL_G1_NC      = 0x222,
    R_AARCH64_TLSLE_MOVW_TPREL_G0         = 0x223,
    R_AARCH64_TLSLE_MOVW_TPREL_G0_NC      = 0x224,
    R_AARCH64_TLSLE_ADD_TPREL_HI12        = 0x225,
    R_AARCH64_TLSLE_ADD_TPREL_LO12        = 0x226,
    R_AARCH64_TLSLE_ADD_TPREL_LO12_NC     = 0x227,
    R_AARCH64_TLSLE_LDST8_TPREL_LO12      = 0x228,
    R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC   = 0x229,
    R_AARCH64_TLSLE_LDST16_TPREL_LO12     = 0x22a,
    R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC  = 0x22b,
    R_AARCH64_TLSLE_LDST32_TPREL_LO12     = 0x22c,
    R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC  = 0x22d,
    R_AARCH64_TLSLE_LDST64_TPREL_LO12     = 0x22e,
    R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC  = 0x22f,

    R_AARCH64_TLSDESC_ADR_PAGE            = 0x232,
    R_AARCH64_TLSDESC_LD64_LO12_NC        = 0x233,
    R_AARCH64_TLSDESC_ADD_LO12_NC         = 0x234,

    R_AARCH64_TLSDESC_CALL                = 0x239
};

enum {
    EF_ARM_SOFT_FLOAT =     0x00000200U,
    EF_ARM_VFP_FLOAT =      0x00000400U,
    EF_ARM_EABI_UNKNOWN =   0x00000000U,
    EF_ARM_EABI_VER1 =      0x01000000U,
    EF_ARM_EABI_VER2 =      0x02000000U,
    EF_ARM_EABI_VER3 =      0x03000000U,
    EF_ARM_EABI_VER4 =      0x04000000U,
    EF_ARM_EABI_VER5 =      0x05000000U,
    EF_ARM_EABIMASK =       0xFF000000U
};

enum {
    R_ARM_NONE                  = 0x00,
    R_ARM_PC24                  = 0x01,
    R_ARM_ABS32                 = 0x02,
    R_ARM_REL32                 = 0x03,
    R_ARM_LDR_PC_G0             = 0x04,
    R_ARM_ABS16                 = 0x05,
    R_ARM_ABS12                 = 0x06,
    R_ARM_THM_ABS5              = 0x07,
    R_ARM_ABS8                  = 0x08,
    R_ARM_SBREL32               = 0x09,
    R_ARM_THM_CALL              = 0x0a,
    R_ARM_THM_PC8               = 0x0b,
    R_ARM_BREL_ADJ              = 0x0c,
    R_ARM_TLS_DESC              = 0x0d,
    R_ARM_THM_SWI8              = 0x0e,
    R_ARM_XPC25                 = 0x0f,
    R_ARM_THM_XPC22             = 0x10,
    R_ARM_TLS_DTPMOD32          = 0x11,
    R_ARM_TLS_DTPOFF32          = 0x12,
    R_ARM_TLS_TPOFF32           = 0x13,
    R_ARM_COPY                  = 0x14,
    R_ARM_GLOB_DAT              = 0x15,
    R_ARM_JUMP_SLOT             = 0x16,
    R_ARM_RELATIVE              = 0x17,
    R_ARM_GOTOFF32              = 0x18,
    R_ARM_BASE_PREL             = 0x19,
    R_ARM_GOT_BREL              = 0x1a,
    R_ARM_PLT32                 = 0x1b,
    R_ARM_CALL                  = 0x1c,
    R_ARM_JUMP24                = 0x1d,
    R_ARM_THM_JUMP24            = 0x1e,
    R_ARM_BASE_ABS              = 0x1f,
    R_ARM_ALU_PCREL_7_0         = 0x20,
    R_ARM_ALU_PCREL_15_8        = 0x21,
    R_ARM_ALU_PCREL_23_15       = 0x22,
    R_ARM_LDR_SBREL_11_0_NC     = 0x23,
    R_ARM_ALU_SBREL_19_12_NC    = 0x24,
    R_ARM_ALU_SBREL_27_20_CK    = 0x25,
    R_ARM_TARGET1               = 0x26,
    R_ARM_SBREL31               = 0x27,
    R_ARM_V4BX                  = 0x28,
    R_ARM_TARGET2               = 0x29,
    R_ARM_PREL31                = 0x2a,
    R_ARM_MOVW_ABS_NC           = 0x2b,
    R_ARM_MOVT_ABS              = 0x2c,
    R_ARM_MOVW_PREL_NC          = 0x2d,
    R_ARM_MOVT_PREL             = 0x2e,
    R_ARM_THM_MOVW_ABS_NC       = 0x2f,
    R_ARM_THM_MOVT_ABS          = 0x30,
    R_ARM_THM_MOVW_PREL_NC      = 0x31,
    R_ARM_THM_MOVT_PREL         = 0x32,
    R_ARM_THM_JUMP19            = 0x33,
    R_ARM_THM_JUMP6             = 0x34,
    R_ARM_THM_ALU_PREL_11_0     = 0x35,
    R_ARM_THM_PC12              = 0x36,
    R_ARM_ABS32_NOI             = 0x37,
    R_ARM_REL32_NOI             = 0x38,
    R_ARM_ALU_PC_G0_NC          = 0x39,
    R_ARM_ALU_PC_G0             = 0x3a,
    R_ARM_ALU_PC_G1_NC          = 0x3b,
    R_ARM_ALU_PC_G1             = 0x3c,
    R_ARM_ALU_PC_G2             = 0x3d,
    R_ARM_LDR_PC_G1             = 0x3e,
    R_ARM_LDR_PC_G2             = 0x3f,
    R_ARM_LDRS_PC_G0            = 0x40,
    R_ARM_LDRS_PC_G1            = 0x41,
    R_ARM_LDRS_PC_G2            = 0x42,
    R_ARM_LDC_PC_G0             = 0x43,
    R_ARM_LDC_PC_G1             = 0x44,
    R_ARM_LDC_PC_G2             = 0x45,
    R_ARM_ALU_SB_G0_NC          = 0x46,
    R_ARM_ALU_SB_G0             = 0x47,
    R_ARM_ALU_SB_G1_NC          = 0x48,
    R_ARM_ALU_SB_G1             = 0x49,
    R_ARM_ALU_SB_G2             = 0x4a,
    R_ARM_LDR_SB_G0             = 0x4b,
    R_ARM_LDR_SB_G1             = 0x4c,
    R_ARM_LDR_SB_G2             = 0x4d,
    R_ARM_LDRS_SB_G0            = 0x4e,
    R_ARM_LDRS_SB_G1            = 0x4f,
    R_ARM_LDRS_SB_G2            = 0x50,
    R_ARM_LDC_SB_G0             = 0x51,
    R_ARM_LDC_SB_G1             = 0x52,
    R_ARM_LDC_SB_G2             = 0x53,
    R_ARM_MOVW_BREL_NC          = 0x54,
    R_ARM_MOVT_BREL             = 0x55,
    R_ARM_MOVW_BREL             = 0x56,
    R_ARM_THM_MOVW_BREL_NC      = 0x57,
    R_ARM_THM_MOVT_BREL         = 0x58,
    R_ARM_THM_MOVW_BREL         = 0x59,
    R_ARM_TLS_GOTDESC           = 0x5a,
    R_ARM_TLS_CALL              = 0x5b,
    R_ARM_TLS_DESCSEQ           = 0x5c,
    R_ARM_THM_TLS_CALL          = 0x5d,
    R_ARM_PLT32_ABS             = 0x5e,
    R_ARM_GOT_ABS               = 0x5f,
    R_ARM_GOT_PREL              = 0x60,
    R_ARM_GOT_BREL12            = 0x61,
    R_ARM_GOTOFF12              = 0x62,
    R_ARM_GOTRELAX              = 0x63,
    R_ARM_GNU_VTENTRY           = 0x64,
    R_ARM_GNU_VTINHERIT         = 0x65,
    R_ARM_THM_JUMP11            = 0x66,
    R_ARM_THM_JUMP8             = 0x67,
    R_ARM_TLS_GD32              = 0x68,
    R_ARM_TLS_LDM32             = 0x69,
    R_ARM_TLS_LDO32             = 0x6a,
    R_ARM_TLS_IE32              = 0x6b,
    R_ARM_TLS_LE32              = 0x6c,
    R_ARM_TLS_LDO12             = 0x6d,
    R_ARM_TLS_LE12              = 0x6e,
    R_ARM_TLS_IE12GP            = 0x6f,
    R_ARM_PRIVATE_0             = 0x70,
    R_ARM_PRIVATE_1             = 0x71,
    R_ARM_PRIVATE_2             = 0x72,
    R_ARM_PRIVATE_3             = 0x73,
    R_ARM_PRIVATE_4             = 0x74,
    R_ARM_PRIVATE_5             = 0x75,
    R_ARM_PRIVATE_6             = 0x76,
    R_ARM_PRIVATE_7             = 0x77,
    R_ARM_PRIVATE_8             = 0x78,
    R_ARM_PRIVATE_9             = 0x79,
    R_ARM_PRIVATE_10            = 0x7a,
    R_ARM_PRIVATE_11            = 0x7b,
    R_ARM_PRIVATE_12            = 0x7c,
    R_ARM_PRIVATE_13            = 0x7d,
    R_ARM_PRIVATE_14            = 0x7e,
    R_ARM_PRIVATE_15            = 0x7f,
    R_ARM_ME_TOO                = 0x80,
    R_ARM_THM_TLS_DESCSEQ16     = 0x81,
    R_ARM_THM_TLS_DESCSEQ32     = 0x82
};

enum {
    EF_MIPS_NOREORDER = 0x00000001,
    EF_MIPS_PIC       = 0x00000002,
    EF_MIPS_CPIC      = 0x00000004,
    EF_MIPS_ABI_O32   = 0x00001000,

    EF_MIPS_MICROMIPS = 0x02000000,
    EF_MIPS_ARCH_ASE_M16 =
        0x04000000,

    EF_MIPS_ARCH_1    = 0x00000000,
    EF_MIPS_ARCH_2    = 0x10000000,
    EF_MIPS_ARCH_3    = 0x20000000,
    EF_MIPS_ARCH_4    = 0x30000000,
    EF_MIPS_ARCH_5    = 0x40000000,
    EF_MIPS_ARCH_32   = 0x50000000,
    EF_MIPS_ARCH_64   = 0x60000000,
    EF_MIPS_ARCH_32R2 = 0x70000000,
    EF_MIPS_ARCH_64R2 = 0x80000000,
    EF_MIPS_ARCH      = 0xf0000000
};

enum {
    R_MIPS_NONE              =  0,
    R_MIPS_16                =  1,
    R_MIPS_32                =  2,
    R_MIPS_REL32             =  3,
    R_MIPS_26                =  4,
    R_MIPS_HI16              =  5,
    R_MIPS_LO16              =  6,
    R_MIPS_GPREL16           =  7,
    R_MIPS_LITERAL           =  8,
    R_MIPS_GOT16             =  9,
    R_MIPS_GOT               =  9,
    R_MIPS_PC16              = 10,
    R_MIPS_CALL16            = 11,
    R_MIPS_GPREL32           = 12,
    R_MIPS_SHIFT5            = 16,
    R_MIPS_SHIFT6            = 17,
    R_MIPS_64                = 18,
    R_MIPS_GOT_DISP          = 19,
    R_MIPS_GOT_PAGE          = 20,
    R_MIPS_GOT_OFST          = 21,
    R_MIPS_GOT_HI16          = 22,
    R_MIPS_GOT_LO16          = 23,
    R_MIPS_SUB               = 24,
    R_MIPS_INSERT_A          = 25,
    R_MIPS_INSERT_B          = 26,
    R_MIPS_DELETE            = 27,
    R_MIPS_HIGHER            = 28,
    R_MIPS_HIGHEST           = 29,
    R_MIPS_CALL_HI16         = 30,
    R_MIPS_CALL_LO16         = 31,
    R_MIPS_SCN_DISP          = 32,
    R_MIPS_REL16             = 33,
    R_MIPS_ADD_IMMEDIATE     = 34,
    R_MIPS_PJUMP             = 35,
    R_MIPS_RELGOT            = 36,
    R_MIPS_JALR              = 37,
    R_MIPS_TLS_DTPMOD32      = 38,
    R_MIPS_TLS_DTPREL32      = 39,
    R_MIPS_TLS_DTPMOD64      = 40,
    R_MIPS_TLS_DTPREL64      = 41,
    R_MIPS_TLS_GD            = 42,
    R_MIPS_TLS_LDM           = 43,
    R_MIPS_TLS_DTPREL_HI16   = 44,
    R_MIPS_TLS_DTPREL_LO16   = 45,
    R_MIPS_TLS_GOTTPREL      = 46,
    R_MIPS_TLS_TPREL32       = 47,
    R_MIPS_TLS_TPREL64       = 48,
    R_MIPS_TLS_TPREL_HI16    = 49,
    R_MIPS_TLS_TPREL_LO16    = 50,
    R_MIPS_GLOB_DAT          = 51,
    R_MIPS_COPY              = 126,
    R_MIPS_JUMP_SLOT         = 127,
    R_MIPS_NUM               = 218
};

enum {
    STO_MIPS_MICROMIPS       = 0x80
};

enum {

    EF_HEXAGON_MACH_V2      = 0x00000001,
    EF_HEXAGON_MACH_V3      = 0x00000002,
    EF_HEXAGON_MACH_V4      = 0x00000003,
    EF_HEXAGON_MACH_V5      = 0x00000004,

    EF_HEXAGON_ISA_MACH     = 0x00000000,

    EF_HEXAGON_ISA_V2       = 0x00000010,
    EF_HEXAGON_ISA_V3       = 0x00000020,
    EF_HEXAGON_ISA_V4       = 0x00000030,
    EF_HEXAGON_ISA_V5       = 0x00000040
};

enum {
    SHN_HEXAGON_SCOMMON     = 0xff00,
    SHN_HEXAGON_SCOMMON_1   = 0xff01,
    SHN_HEXAGON_SCOMMON_2   = 0xff02,
    SHN_HEXAGON_SCOMMON_4   = 0xff03,
    SHN_HEXAGON_SCOMMON_8   = 0xff04
};

enum {
    R_HEX_NONE              =  0,
    R_HEX_B22_PCREL         =  1,
    R_HEX_B15_PCREL         =  2,
    R_HEX_B7_PCREL          =  3,
    R_HEX_LO16              =  4,
    R_HEX_HI16              =  5,
    R_HEX_32                =  6,
    R_HEX_16                =  7,
    R_HEX_8                 =  8,
    R_HEX_GPREL16_0         =  9,
    R_HEX_GPREL16_1         =  10,
    R_HEX_GPREL16_2         =  11,
    R_HEX_GPREL16_3         =  12,
    R_HEX_HL16              =  13,
    R_HEX_B13_PCREL         =  14,
    R_HEX_B9_PCREL          =  15,
    R_HEX_B32_PCREL_X       =  16,
    R_HEX_32_6_X            =  17,
    R_HEX_B22_PCREL_X       =  18,
    R_HEX_B15_PCREL_X       =  19,
    R_HEX_B13_PCREL_X       =  20,
    R_HEX_B9_PCREL_X        =  21,
    R_HEX_B7_PCREL_X        =  22,
    R_HEX_16_X              =  23,
    R_HEX_12_X              =  24,
    R_HEX_11_X              =  25,
    R_HEX_10_X              =  26,
    R_HEX_9_X               =  27,
    R_HEX_8_X               =  28,
    R_HEX_7_X               =  29,
    R_HEX_6_X               =  30,
    R_HEX_32_PCREL          =  31,
    R_HEX_COPY              =  32,
    R_HEX_GLOB_DAT          =  33,
    R_HEX_JMP_SLOT          =  34,
    R_HEX_RELATIVE          =  35,
    R_HEX_PLT_B22_PCREL     =  36,
    R_HEX_GOTREL_LO16       =  37,
    R_HEX_GOTREL_HI16       =  38,
    R_HEX_GOTREL_32         =  39,
    R_HEX_GOT_LO16          =  40,
    R_HEX_GOT_HI16          =  41,
    R_HEX_GOT_32            =  42,
    R_HEX_GOT_16            =  43,
    R_HEX_DTPMOD_32         =  44,
    R_HEX_DTPREL_LO16       =  45,
    R_HEX_DTPREL_HI16       =  46,
    R_HEX_DTPREL_32         =  47,
    R_HEX_DTPREL_16         =  48,
    R_HEX_GD_PLT_B22_PCREL  =  49,
    R_HEX_GD_GOT_LO16       =  50,
    R_HEX_GD_GOT_HI16       =  51,
    R_HEX_GD_GOT_32         =  52,
    R_HEX_GD_GOT_16         =  53,
    R_HEX_IE_LO16           =  54,
    R_HEX_IE_HI16           =  55,
    R_HEX_IE_32             =  56,
    R_HEX_IE_GOT_LO16       =  57,
    R_HEX_IE_GOT_HI16       =  58,
    R_HEX_IE_GOT_32         =  59,
    R_HEX_IE_GOT_16         =  60,
    R_HEX_TPREL_LO16        =  61,
    R_HEX_TPREL_HI16        =  62,
    R_HEX_TPREL_32          =  63,
    R_HEX_TPREL_16          =  64,
    R_HEX_6_PCREL_X         =  65,
    R_HEX_GOTREL_32_6_X     =  66,
    R_HEX_GOTREL_16_X       =  67,
    R_HEX_GOTREL_11_X       =  68,
    R_HEX_GOT_32_6_X        =  69,
    R_HEX_GOT_16_X          =  70,
    R_HEX_GOT_11_X          =  71,
    R_HEX_DTPREL_32_6_X     =  72,
    R_HEX_DTPREL_16_X       =  73,
    R_HEX_DTPREL_11_X       =  74,
    R_HEX_GD_GOT_32_6_X     =  75,
    R_HEX_GD_GOT_16_X       =  76,
    R_HEX_GD_GOT_11_X       =  77,
    R_HEX_IE_32_6_X         =  78,
    R_HEX_IE_16_X           =  79,
    R_HEX_IE_GOT_32_6_X     =  80,
    R_HEX_IE_GOT_16_X       =  81,
    R_HEX_IE_GOT_11_X       =  82,
    R_HEX_TPREL_32_6_X      =  83,
    R_HEX_TPREL_16_X        =  84,
    R_HEX_TPREL_11_X        =  85
};

enum {
    R_390_NONE        =  0,
    R_390_8           =  1,
    R_390_12          =  2,
    R_390_16          =  3,
    R_390_32          =  4,
    R_390_PC32        =  5,
    R_390_GOT12       =  6,
    R_390_GOT32       =  7,
    R_390_PLT32       =  8,
    R_390_COPY        =  9,
    R_390_GLOB_DAT    = 10,
    R_390_JMP_SLOT    = 11,
    R_390_RELATIVE    = 12,
    R_390_GOTOFF      = 13,
    R_390_GOTPC       = 14,
    R_390_GOT16       = 15,
    R_390_PC16        = 16,
    R_390_PC16DBL     = 17,
    R_390_PLT16DBL    = 18,
    R_390_PC32DBL     = 19,
    R_390_PLT32DBL    = 20,
    R_390_GOTPCDBL    = 21,
    R_390_64          = 22,
    R_390_PC64        = 23,
    R_390_GOT64       = 24,
    R_390_PLT64       = 25,
    R_390_GOTENT      = 26,
    R_390_GOTOFF16    = 27,
    R_390_GOTOFF64    = 28,
    R_390_GOTPLT12    = 29,
    R_390_GOTPLT16    = 30,
    R_390_GOTPLT32    = 31,
    R_390_GOTPLT64    = 32,
    R_390_GOTPLTENT   = 33,
    R_390_PLTOFF16    = 34,
    R_390_PLTOFF32    = 35,
    R_390_PLTOFF64    = 36,
    R_390_TLS_LOAD    = 37,
    R_390_TLS_GDCALL  = 38,
    R_390_TLS_LDCALL  = 39,
    R_390_TLS_GD32    = 40,
    R_390_TLS_GD64    = 41,
    R_390_TLS_GOTIE12 = 42,
    R_390_TLS_GOTIE32 = 43,
    R_390_TLS_GOTIE64 = 44,
    R_390_TLS_LDM32   = 45,
    R_390_TLS_LDM64   = 46,
    R_390_TLS_IE32    = 47,
    R_390_TLS_IE64    = 48,
    R_390_TLS_IEENT   = 49,
    R_390_TLS_LE32    = 50,
    R_390_TLS_LE64    = 51,
    R_390_TLS_LDO32   = 52,
    R_390_TLS_LDO64   = 53,
    R_390_TLS_DTPMOD  = 54,
    R_390_TLS_DTPOFF  = 55,
    R_390_TLS_TPOFF   = 56,
    R_390_20          = 57,
    R_390_GOT20       = 58,
    R_390_GOTPLT20    = 59,
    R_390_TLS_GOTIE20 = 60,
    R_390_IRELATIVE   = 61
};

struct Elf32_Shdr {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
};

struct Elf64_Shdr {
    Elf64_Word  sh_name;
    Elf64_Word  sh_type;
    Elf64_Xword sh_flags;
    Elf64_Addr  sh_addr;
    Elf64_Off   sh_offset;
    Elf64_Xword sh_size;
    Elf64_Word  sh_link;
    Elf64_Word  sh_info;
    Elf64_Xword sh_addralign;
    Elf64_Xword sh_entsize;
};

enum {
    SHN_UNDEF     = 0,
    SHN_LORESERVE = 0xff00,
    SHN_LOPROC    = 0xff00,
    SHN_HIPROC    = 0xff1f,
    SHN_LOOS      = 0xff20,
    SHN_HIOS      = 0xff3f,
    SHN_ABS       = 0xfff1,
    SHN_COMMON    = 0xfff2,
    SHN_XINDEX    = 0xffff,
    SHN_HIRESERVE = 0xffff
};

enum {
    SHT_NULL          = 0,
    SHT_PROGBITS      = 1,
    SHT_SYMTAB        = 2,
    SHT_STRTAB        = 3,
    SHT_RELA          = 4,
    SHT_HASH          = 5,
    SHT_DYNAMIC       = 6,
    SHT_NOTE          = 7,
    SHT_NOBITS        = 8,
    SHT_REL           = 9,
    SHT_SHLIB         = 10,
    SHT_DYNSYM        = 11,
    SHT_INIT_ARRAY    = 14,
    SHT_FINI_ARRAY    = 15,
    SHT_PREINIT_ARRAY = 16,
    SHT_GROUP         = 17,
    SHT_SYMTAB_SHNDX  = 18,
    SHT_LOOS          = 0x60000000,
    SHT_GNU_ATTRIBUTES = 0x6ffffff5,
    SHT_GNU_HASH      = 0x6ffffff6,
    SHT_GNU_verdef    = 0x6ffffffd,
    SHT_GNU_verneed   = 0x6ffffffe,
    SHT_GNU_versym    = 0x6fffffff,
    SHT_HIOS          = 0x6fffffff,
    SHT_LOPROC        = 0x70000000,

    SHT_ARM_EXIDX           = 0x70000001U,

    SHT_ARM_PREEMPTMAP      = 0x70000002U,

    SHT_ARM_ATTRIBUTES      = 0x70000003U,
    SHT_ARM_DEBUGOVERLAY    = 0x70000004U,
    SHT_ARM_OVERLAYSECTION  = 0x70000005U,
    SHT_HEX_ORDERED         = 0x70000000,

    SHT_X86_64_UNWIND       = 0x70000001,

    SHT_MIPS_REGINFO        = 0x70000006,
    SHT_MIPS_OPTIONS        = 0x7000000d,

    SHT_HIPROC        = 0x7fffffff,
    SHT_LOUSER        = 0x80000000,
    SHT_HIUSER        = 0xffffffff
};

enum {

    SHF_WRITE = 0x1,

    SHF_ALLOC = 0x2,

    SHF_EXECINSTR = 0x4,

    SHF_MERGE = 0x10,

    SHF_STRINGS = 0x20,

    SHF_INFO_LINK = 0x40U,

    SHF_LINK_ORDER = 0x80U,

    SHF_OS_NONCONFORMING = 0x100U,

    SHF_GROUP = 0x200U,

    SHF_TLS = 0x400U,

    XCORE_SHF_CP_SECTION = 0x800U,

    XCORE_SHF_DP_SECTION = 0x1000U,

    SHF_MASKOS   = 0x0ff00000,

    SHF_MASKPROC = 0xf0000000,

    SHF_X86_64_LARGE = 0x10000000,

    SHF_HEX_GPREL = 0x10000000,

    SHF_MIPS_NOSTRIP = 0x8000000
};

enum {
    GRP_COMDAT = 0x1,
    GRP_MASKOS = 0x0ff00000,
    GRP_MASKPROC = 0xf0000000
};

struct Elf32_Sym {
    Elf32_Word    st_name;
    Elf32_Addr    st_value;
    Elf32_Word    st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half    st_shndx;
};

struct Elf64_Sym {
    Elf64_Word      st_name;
    unsigned char   st_info;
    unsigned char   st_other;
    Elf64_Half      st_shndx;
    Elf64_Addr      st_value;
    Elf64_Xword     st_size;
};

enum {
    SYMENTRY_SIZE32 = 16,
    SYMENTRY_SIZE64 = 24
};

enum {
    STB_LOCAL = 0,
    STB_GLOBAL = 1,
    STB_WEAK = 2,
    STB_LOOS   = 10,
    STB_HIOS   = 12,
    STB_LOPROC = 13,
    STB_HIPROC = 15
};

enum {
    STT_NOTYPE  = 0,
    STT_OBJECT  = 1,
    STT_FUNC    = 2,
    STT_SECTION = 3,
    STT_FILE    = 4,
    STT_COMMON  = 5,
    STT_TLS     = 6,
    STT_LOOS    = 7,
    STT_HIOS    = 8,
    STT_GNU_IFUNC = 10,
    STT_LOPROC  = 13,
    STT_HIPROC  = 15
};

enum {
    STV_DEFAULT   = 0,
    STV_INTERNAL  = 1,
    STV_HIDDEN    = 2,
    STV_PROTECTED = 3
};

enum {
    STN_UNDEF = 0
};

struct Elf32_Rel {
    Elf32_Addr r_offset;
    Elf32_Word r_info;
};

struct Elf32_Rela {
    Elf32_Addr  r_offset;
    Elf32_Word  r_info;
    Elf32_Sword r_addend;
};

struct Elf64_Rel {
    Elf64_Addr r_offset;
    Elf64_Xword r_info;
};

struct Elf64_Rela {
    Elf64_Addr  r_offset;
    Elf64_Xword  r_info;
    Elf64_Sxword r_addend;
};

struct Elf32_Phdr {
    Elf32_Word p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    Elf32_Word p_filesz;
    Elf32_Word p_memsz;
    Elf32_Word p_flags;
    Elf32_Word p_align;
};

struct Elf64_Phdr {
    Elf64_Word   p_type;
    Elf64_Word   p_flags;
    Elf64_Off    p_offset;
    Elf64_Addr   p_vaddr;
    Elf64_Addr   p_paddr;
    Elf64_Xword  p_filesz;
    Elf64_Xword  p_memsz;
    Elf64_Xword  p_align;
};

enum {
    PT_NULL    = 0,
    PT_LOAD    = 1,
    PT_DYNAMIC = 2,
    PT_INTERP  = 3,
    PT_NOTE    = 4,
    PT_SHLIB   = 5,
    PT_PHDR    = 6,
    PT_TLS     = 7,
    PT_LOOS    = 0x60000000,
    PT_HIOS    = 0x6fffffff,
    PT_LOPROC  = 0x70000000,
    PT_HIPROC  = 0x7fffffff,

    PT_GNU_EH_FRAME  = 0x6474e550,
    PT_SUNW_EH_FRAME = 0x6474e550,
    PT_SUNW_UNWIND   = 0x6464e550,

    PT_GNU_STACK  = 0x6474e551,
    PT_GNU_RELRO  = 0x6474e552,

    PT_ARM_ARCHEXT = 0x70000000,

    PT_ARM_EXIDX   = 0x70000001,
    PT_ARM_UNWIND  = 0x70000001
};

enum {
    PF_X        = 1,
    PF_W        = 2,
    PF_R        = 4,
    PF_MASKOS   = 0x0ff00000,
    PF_MASKPROC = 0xf0000000
};

struct Elf32_Dyn
{
    Elf32_Sword d_tag;
    union
    {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
};

struct Elf64_Dyn
{
    Elf64_Sxword d_tag;
    union
    {
        Elf64_Xword d_val;
        Elf64_Addr  d_ptr;
    } d_un;
};

enum {
    DT_NULL         = 0,
    DT_NEEDED       = 1,
    DT_PLTRELSZ     = 2,
    DT_PLTGOT       = 3,
    DT_HASH         = 4,
    DT_STRTAB       = 5,
    DT_SYMTAB       = 6,
    DT_RELA         = 7,
    DT_RELASZ       = 8,
    DT_RELAENT      = 9,
    DT_STRSZ        = 10,
    DT_SYMENT       = 11,
    DT_INIT         = 12,
    DT_FINI         = 13,
    DT_SONAME       = 14,
    DT_RPATH        = 15,
    DT_SYMBOLIC     = 16,
    DT_REL          = 17,
    DT_RELSZ        = 18,
    DT_RELENT       = 19,
    DT_PLTREL       = 20,
    DT_DEBUG        = 21,
    DT_TEXTREL      = 22,
    DT_JMPREL       = 23,
    DT_BIND_NOW     = 24,
    DT_INIT_ARRAY   = 25,
    DT_FINI_ARRAY   = 26,
    DT_INIT_ARRAYSZ = 27,
    DT_FINI_ARRAYSZ = 28,
    DT_RUNPATH      = 29,
    DT_FLAGS        = 30,
    DT_ENCODING     = 32,

    DT_PREINIT_ARRAY = 32,
    DT_PREINIT_ARRAYSZ = 33,

    DT_LOOS         = 0x60000000,
    DT_HIOS         = 0x6FFFFFFF,
    DT_LOPROC       = 0x70000000,
    DT_HIPROC       = 0x7FFFFFFF,

    DT_RELACOUNT    = 0x6FFFFFF9,
    DT_RELCOUNT     = 0x6FFFFFFA,

    DT_FLAGS_1      = 0X6FFFFFFB,
    DT_VERDEF       = 0X6FFFFFFC,
    DT_VERDEFNUM    = 0X6FFFFFFD,
    DT_VERNEED      = 0X6FFFFFFE,
    DT_VERNEEDNUM   = 0X6FFFFFFF
};

enum {
    DF_ORIGIN     = 0x01,
    DF_SYMBOLIC   = 0x02,
    DF_TEXTREL    = 0x04,
    DF_BIND_NOW   = 0x08,
    DF_STATIC_TLS = 0x10
};

enum {
    DF_1_NOW        = 0x00000001,
    DF_1_GLOBAL     = 0x00000002,
    DF_1_GROUP      = 0x00000004,
    DF_1_NODELETE   = 0x00000008,
    DF_1_LOADFLTR   = 0x00000010,
    DF_1_INITFIRST  = 0x00000020,
    DF_1_NOOPEN     = 0x00000040,
    DF_1_ORIGIN     = 0x00000080,
    DF_1_DIRECT     = 0x00000100,
    DF_1_TRANS      = 0x00000200,
    DF_1_INTERPOSE  = 0x00000400,
    DF_1_NODEFLIB   = 0x00000800,
    DF_1_NODUMP     = 0x00001000,
    DF_1_CONFALT    = 0x00002000,
    DF_1_ENDFILTEE  = 0x00004000,
    DF_1_DISPRELDNE = 0x00008000,
    DF_1_DISPRELPND = 0x00010000
};

enum {
    VER_DEF_NONE    = 0,
    VER_DEF_CURRENT = 1
};

enum {
    VER_FLG_BASE = 0x1,
    VER_FLG_WEAK = 0x2,
    VER_FLG_INFO = 0x4
};

enum {
    VER_NDX_LOCAL  = 0,
    VER_NDX_GLOBAL = 1,
    VERSYM_VERSION = 0x7fff,
    VERSYM_HIDDEN  = 0x8000
};

enum {
    VER_NEED_NONE = 0,
    VER_NEED_CURRENT = 1
};

static inline struct Elf64_Phdr *elf_pheader(struct Elf64_Ehdr *hdr) {
    if (!hdr->e_phoff) {
        return 0;
    }

    return (struct Elf64_Phdr *)((uint64_t)hdr + hdr->e_phoff);
}

static inline struct Elf64_Phdr *elf_segment(struct Elf64_Ehdr *hdr, int idx) {
    uint64_t addr = (uint64_t)elf_pheader(hdr);
    if (!addr) {
        return 0;
    }

    return (struct Elf64_Phdr *)(addr + (hdr->e_phentsize * idx));
}

static inline struct Elf64_Shdr *elf_sheader(struct Elf64_Ehdr *hdr) {
    if (!hdr->e_shoff) {
        return 0;
    }

    return (struct Elf64_Shdr *)((uint64_t)hdr + hdr->e_shoff);
}

static inline struct Elf64_Shdr *elf_section(struct Elf64_Ehdr *hdr, int idx) {
    uint64_t addr = (uint64_t)elf_sheader(hdr);
    if (!addr) {
        return 0;
    }

    return (struct Elf64_Shdr *)(addr + (hdr->e_shentsize * idx));
}

int elf_mapped_size(void *elf, uint64_t *msize);

#endif
