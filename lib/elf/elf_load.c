#include <efi.h>
#include <elf/elf.h>






efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;

	if (!fd->elf_fd) {
		return EFI_NOT_FOUND;
	}

	// Validate once again this is an ELF executable
	if (elf_validate(fd) == false) {
		printf(L"Non-ELF executable detected!\n");
		return EFI_NOT_FOUND;
	}

	if (elf_is_supported_arch(fd) == false) {
		printf(L"ELF architecture not supported!\n");
		return EFI_NOT_FOUND;
	}

	switch(fd->elf_hdr->e_type) {
		case ET_NONE:
			break;

		case ET_REL:
			break;

		case ET_EXEC:
			ret = elf_load_phdrs(fd);
			break;

		case ET_DYN:
			break;
	}

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}
