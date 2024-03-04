#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_shdr_t *shdr = NULL;



	ret = elf_check(fd);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to load ELF! (%r)\n", ret);
		return ret;
	}

	for (uint64_t i = 0; i < hdr->e_shnum; i++) {
		shdr = elf_for_each_shdr(fd, i);

		if (shdr->sh_type == SHT_NULL) {
			// NULL segment
			continue;
		}

		if (shdr->sh_type == SHT_NOBITS) {
			// Section needs allocation

			if (shdr->sh_size <= 0) {
				// Empty section
				continue;
			}

			if (shdr->sh_flags & SHF_ALLOC) {
				// Allocate section
				void *buf = alloc(shdr->sh_size);
				memset(buf, 0, shdr->sh_size);

				elf64_off_t hdr_off = (elf64_off_t)hdr;
				elf64_off_t buf_off = (elf64_off_t)buf;

				// Set offset to allocated buffer
				shdr->sh_offset = hdr_off - buff_off;
			}
		}

		free(shdr);
	}

	return EFI_SUCCESS;
}
