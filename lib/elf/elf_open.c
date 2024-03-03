#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	elf_fd_t *fd = alloc(sizeof(elf_fd_t));
	uint64_t file_size = 0;

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

	// Get ELF file information
	file_size = fd->elf_info->file_size;
	fd->elf_data = alloc(file_size);

	if (!fd->elf_data) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	// Read ELF data
	fseek(fd->elf_fd, 0);
	fread(fd->elf_fd, fd->elf_data, file_size);

	// After the ELF file is read into memory we
	// no longer need the file descriptor to be open
	fclose(fd->elf_fd);

	return fd;
}
