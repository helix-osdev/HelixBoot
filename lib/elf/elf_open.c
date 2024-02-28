#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	elf_fd_t *elf = malloc(sizeof(elf_fd_t));

	elf->fd = fopen(name);
	elf->elf_hdr = malloc(sizeof(elf64_ehdr_t));

	if (!elf->fd) {
		printf(L"Failed to open %s\n", name);
		return NULL;
	}	

	fseek(elf->fd, 0);
	fread(elf->fd, elf->elf_hdr, sizeof(elf64_ehdr_t));

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
