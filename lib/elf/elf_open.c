#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	elf_fd_t *elf = alloc(sizeof(elf_fd_t));

	elf->elf_fd = fopen(name);
	elf->elf_hdr = alloc(sizeof(elf64_ehdr_t));

	if (!elf->elf_fd) {
		printf(L"Failed to open %s\n", name);
		return NULL;
	}	

	fseek(elf->elf_fd, 0);
	fread(elf->elf_fd, elf->elf_hdr, sizeof(elf64_ehdr_t));

	// Validate that this is an ELF executable
	// otherwise reject it
	if (elf_validate(elf) == false) {
		printf(L"Non-ELF executable detected!\n");
		return NULL;
	}

	if (elf_is_supported_arch(elf) == false) {
		printf(L"ELF architecture not supported!\n");
		return NULL;
	}
	
	return elf;
}
