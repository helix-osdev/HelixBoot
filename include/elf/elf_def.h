#ifndef ELF_DEF_H
#define ELF_DEF_H

#include <efi.h>


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



typedef struct {
	uint8_t		e_ident[MAX_ELF_IDENT];
	uint16_t	e_type;
	uint16_t	e_machine;
	uint64_t	e_entry;
	uint64_t	e_phoff;
	uint64_t	e_shoff;
	uint64_t	e_flags;
	uint16_t	e_ehsize;
	uint16_t	e_phentsize;
	uint16_t	e_phnum;
	uint16_t	e_shentsize;
	uint16_t	e_shnum;
	uint16_t	e_shstrndx;
} elf64_ehdr_t;

typedef struct {
	uint32_t	p_type;
	uint32_t	p_flags;
	uint64_t	p_offset;
	uint64_t	p_vaddr;
	uint64_t	p_paddr;
	uint64_t	p_filesz;
	uint64_t	p_memsz;
	uint64_t	p_align;
} elf64_phdr_t;

typedef struct {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
} elf64_shdr_t;

typedef struct {
    uint64_t r_addr;
    uint32_t r_info;
    uint32_t r_symbol;
    uint64_t r_addend;
} elf64_rela_t;

typedef struct {
    uint64_t d_tag;
    uint64_t d_un;
} elf_dyn_t;

typedef struct {
	efi_file_proto_t	*elf_fd;
	efi_file_info_t		*elf_info;
	elf64_ehdr_t		*elf_hdr;
} elf_fd_t;

#endif
