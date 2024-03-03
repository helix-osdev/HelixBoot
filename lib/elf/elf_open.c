#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






elf_fd_t *elf_open(char16_t *name) {
	efi_status_t ret = 0;
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

	// Validate ELF executable
	ret = elf_check(fd->elf_data);

	if (EFI_ERROR(ret)) {
		printf(L"Invalid ELF executable: %s! (%r)\n", fd->elf_info->file_name, ret);

		// Cleanup data
		free(fd->elf_info);
		free(fd->elf_data);
		fclose(fd->elf_fd);
		return NULL;
	}

	// After the ELF file is read into memory we
	// no longer need the file descriptor to be open
	fclose(fd->elf_fd);

	return fd;
}
