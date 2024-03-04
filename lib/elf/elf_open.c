#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	efi_status_t ret = 0;
	elf_fd_t *fd = alloc(sizeof(elf_fd_t));




	if (!fd) {
		return NULL;
	}

	fd->elf_fd = fopen(name);

	if (!fd->elf_fd) {
		printf(L"elf: failed to open %s!\n", name);
		return NULL;
	}

	fd->elf_info = get_file_info(fd->elf_fd);

	if (!fd->elf_info) {
		printf(L"elf: failed to get file info!\n");
		return NULL;
	}

	fd->elf_hdr = alloc(sizeof(elf64_ehdr_t));

	if (!fd->elf_hdr) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	fseek(fd->elf_fd, 0);
	fread(fd->elf_fd, fd->elf_hdr, sizeof(elf64_ehdr_t));

	ret = elf_check(fd);

	if (EFI_ERROR(ret)) {
		elf_close(fd);
		return NULL;
	}

	return fd;
}
