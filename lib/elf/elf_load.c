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

				// TODO:
				// Check section's sizes and ensure that
				// if they end up in the same region and
				// ensure that we allocate each address
				// for each one
				ret = elf_load_phdr(fd, phdr);

				if (EFI_ERROR(ret)) {
					printf(L"elf: failed to load segment @ index %u\n", i);
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


	/*
	for (uint64_t i = 0; i < hdr->e_shnum; i++) {
		shdr = elf_for_each_shdr(fd, i);

		switch(shdr->sh_type) {
			case SHT_NOBITS:
				if (shdr->sh_size <= 0) {
					// NULL segment
					continue;
				}

				switch(shdr->sh_flags) {
					case SHF_ALLOC:
						// Allocate section
						void *buf = elf_alloc(shdr->sh_size);
						memset(buf, 0, shdr->sh_size);

						elf64_off_t hdr_off = (elf64_off_t)hdr;
						elf64_off_t buf_off = (elf64_off_t)buf;

						// Set offset to allocated buffer
						shdr->sh_offset = hdr_off - buf_off;
					case SHF_WRITE:
						// TODO:
						// Map as writable
						break;

					default:
						break;
				}

				break;

			default:
				break;
		}
	}
	*/

	return EFI_SUCCESS;
}
