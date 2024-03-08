#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_shdr_t *shdr = NULL;
	elf64_phdr_t *phdr = NULL;



	ret = elf_check(fd);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to load ELF! (%r)\n", ret);
		return ret;
	}


	switch(hdr->e_type) {
		case ET_EXEC:
			for (uint64_t i = 0; i < hdr->e_phnum; i++) {
				phdr = elf_for_each_phdr(fd, i);

				ret = elf_load_phdr(fd, phdr);

				if (EFI_ERROR(ret)) {
					printf(L"elf: failed to load phdr segment @ index %u\n", i);
					return ret;
				}
			}

			for (uint64_t j = 0; j < hdr->e_shnum; j++) {
				shdr = elf_for_each_shdr(fd, j);

				ret = elf_load_shdr(fd, shdr);

				if (EFI_ERROR(ret)) {
					printf(L"elf: failed to load shdr segment @ index %u\n", j);
					return ret;
				}
			}

			break;

		case ET_DYN:
			// Load dynamic
			break;

		case ET_REL:
			// Relocation
			break;

		default:
			break;
	}

	return EFI_SUCCESS;
}
