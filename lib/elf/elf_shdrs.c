#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








elf64_shdr_t *elf_for_each_shdr(elf_fd_t *fd, elf64_xword_t index) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_shdr_t *shdr = NULL;
	elf64_off_t offset = 0;


	offset = hdr->e_shoff + index * hdr->e_shentsize;
	shdr = elf_alloc(hdr->e_shentsize);

	if (!shdr) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	fseek(fd->elf_fd, offset);
	fread(fd->elf_fd, shdr, hdr->e_shentsize);

	return shdr;
}


efi_status_t elf_load_shdr(elf_fd_t *fd, elf64_shdr_t *shdr) {
	efi_status_t ret = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_off_t hdr_off = 0, buf_off = 0;
	elf64_xword_t sh_size = 0;
	void *buf = NULL;



	switch(shdr->sh_type) {
		case SHT_NOBITS:
			sh_size = shdr->sh_size;
			buf = elf_alloc(sh_size);

			if (!buf) {
				printf(L"elf: out of resources!\n");
				return EFI_LOAD_ERROR;
			}

			hdr_off = (elf64_off_t)hdr;
			buf_off = (elf64_off_t)buf;

			switch(shdr->sh_flags) {
				case SHF_ALLOC:
					// Allocate section
					buf = elf_alloc(sh_size);
					memset(buf, 0, sh_size);

					// Set offset to allocated buffer
					shdr->sh_offset = hdr_off - buf_off;

					break;

				default:
					break;
			}

			break;

		default:
			break;
	}

	return EFI_SUCCESS;
}
