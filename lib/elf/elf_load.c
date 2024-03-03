#include <efi.h>
#include <elf/elf.h>






efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_data;


	ret = elf_check(fd->elf_data);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to load ELF! (%r)\n", ret);
		return ret;
	}

	return EFI_SUCCESS;
}
