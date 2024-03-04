#include <efi.h>
#include <elf/elf.h>






efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_phdr_t *phdr = NULL;


	ret = elf_check(fd);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to load ELF! (%r)\n", ret);
		return ret;
	}

	for (uint64_t i = 0; i < hdr->e_phnum; i++) {
		phdr = elf_for_each_phdr(fd, i);

		printf(L"Size: %u\n", phdr->p_filesz);
		printf(L"Phys: %x\n", phdr->p_paddr);

		free(phdr);
	}

	return EFI_SUCCESS;
}
