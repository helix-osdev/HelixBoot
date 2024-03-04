#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>





void elf_close(elf_fd_t *fd) {
	if (fd) {
		if (fd->elf_fd) {
			fclose(fd->elf_fd);
		}

		if (fd->elf_hdr) {
			free(fd->elf_hdr);
		}

		if (fd->elf_info) {
			free(fd->elf_info);
		}
	}
}
