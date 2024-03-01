#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






void elf_close(elf_fd_t *fd) {
	if (fd) {
		if (fd->elf_fd) {
			fclose(fd->elf_fd);
		}
	}
}
