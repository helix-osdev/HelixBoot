#ifndef ELF_DEF_H
#define ELF_DEF_H

#include <efi.h>


typedef uint16_t elf64_half_t;

typedef uint32_t elf64_word_t;
typedef int32_t elf64_sword_t;
typedef uint64_t elf64_xword_t;
typedef int64_t elf64_sxword_t;

typedef uint64_t elf64_addr_t;
typedef uint64_t elf64_off_t;

typedef uint16_t elf64_section_t;

typedef elf64_half_t elf64_versym_t;



#define MAX_ELF_IDENT 16

#define EI_MAG0		0
#define EI_MAG1		1
#define EI_MAG2		2
#define EI_MAG3		3

#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'

#define EI_CLASS	4
#define EI_DATA		5
#define EI_VERSION	6
#define EI_OSABI	7

#define ELFCLASS64	2

#define EI_DATA		5
#define ELFDATALSB	1

#define ELFOSABI_SYSV		0
#define ELFOSABI_ARM		97
#define ELFOSABI_ARM_EABI	64

#define EI_ABIVERSION	8
#define EI_PAD			9

#define ET_NONE			0
#define ET_REL			1
#define ET_EXEC			2
#define ET_DYN			3

#define EM_NONE		0
#define EM_ARM		40
#define EM_AARCH64	183

#define EV_NONE		0
#define EV_CURRENT	1
#define EV_NUM		2

#define PF_R	0x4
#define PF_W	0x2
#define PF_X	0x1

#define PT_LOAD     0x00000001
#define PT_DYNAMIC  0x00000002
#define PT_INTERP   0x00000003
#define PT_PHDR     0x00000006

#define DT_NULL     0x00000000
#define DT_NEEDED   0x00000001
#define DT_RELA     0x00000007
#define DT_RELASZ   0x00000008
#define DT_RELAENT  0x00000009
#define DT_FLAGS_1  0x6ffffffb

#define DF_1_PIE    0x08000000

#define SHT_NULL		0x00000000
#define SHT_PROGBITS	0x00000001
#define SHT_SYMTAB		0x00000002
#define SHT_STRTAB		0x00000003
#define SHT_RELA    	0x00000004
#define SHT_NOBITS		0x00000008
#define SHT_REL			0x00000009
#define SHT_SHLIB		10
#define SHT_DYNSYM		11
#define SHT_INIT_ARRAY	14
#define SHT_FINI_ARRAY	15
#define SHT_GROUP		17
#define SHT_SYMTAB_SHNDX 18
#define SHT_NUM			19

#define SHF_WRITE	(1 << 0)
#define SHF_ALLOC	(1 << 1)

#define SHN_UNDEF	0

#define ARCH_AARCH64	0xb7

#define R_AARCH64_RELATIVE 0x00000403

#define ELF64_ST_BIND(x)   	((x) >> 4)
#define ELF64_ST_TYPE(x)   	((x) & 0xf)
#define ELF64_ST_INFO(x, y) (((x) << 4) + ((y) & 0xf))

#define ELF32_ST_VISIBILITY(x) ((x) & 0x3)
#define ELF64_ST_VISIBILITY(x) ((x) & 0x3)






typedef struct {
	uint8_t			e_ident[MAX_ELF_IDENT];
	elf64_half_t	e_type;
	elf64_half_t	e_machine;
	elf64_word_t	e_version;
	elf64_addr_t	e_entry;
	elf64_off_t		e_phoff;
	elf64_off_t		e_shoff;
	elf64_word_t	e_flags;
	elf64_half_t	e_ehsize;
	elf64_half_t	e_phentsize;
	elf64_half_t	e_phnum;
	elf64_half_t	e_shentsize;
	elf64_half_t	e_shnum;
	elf64_half_t	e_shstrndx;
} elf64_ehdr_t;

typedef struct {
	elf64_word_t	p_type;
	elf64_word_t	p_flags;
	elf64_off_t		p_offset;
	elf64_addr_t	p_vaddr;
	elf64_addr_t	p_paddr;
	elf64_xword_t	p_filesz;
	elf64_xword_t	p_memsz;
	elf64_xword_t	p_align;
} elf64_phdr_t;

typedef struct {
    elf64_word_t 	sh_name;
    elf64_word_t	sh_type;
    elf64_xword_t	sh_flags;
    elf64_addr_t	sh_addr;
    elf64_off_t		sh_offset;;
    elf64_xword_t	sh_size;
    elf64_word_t	sh_link;
    elf64_word_t	sh_info;
    elf64_xword_t 	sh_addralign;
    elf64_xword_t	sh_entsize;
} elf64_shdr_t;

typedef struct {
	elf64_addr_t	r_offset;
	elf64_xword_t	r_info;
} elf64_rel_t;

typedef struct {
    elf64_addr_t	r_offset;
    elf64_xword_t	r_info;
    elf64_sxword_t	r_addend;
} elf64_rela_t;

typedef struct {
    uint64_t d_tag;
    uint64_t d_un;
} elf_dyn_t;

typedef struct {
	elf64_word_t	st_name;
	uint8_t			st_info;
	uint8_t			st_other;
	elf64_section_t	st_shndx;
	elf64_addr_t	st_value;
	elf64_xword_t	st_size;
} elf64_sym_t;

typedef struct {
	elf64_half_t	si_bound_to;
	elf64_half_t	si_flags;
} elf64_sym_info_t;

typedef struct {
	efi_file_proto_t	*elf_fd;
	efi_file_info_t		*elf_info;
	elf64_ehdr_t		*elf_hdr;
} elf_fd_t;

#endif
