#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	elf_fd_t *fd = alloc(sizeof(elf_fd_t));

	if (!fd) {
		return NULL;
	}

	fd->elf_fd = fopen(name);

	return fd;
}
