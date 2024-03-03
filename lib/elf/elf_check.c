#include <efi.h>
#include <elf/elf.h>




efi_status_t elf_check(void *buf) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)buf;

	if (hdr->e_ident[EI_MAG0] != ELFMAG0 &&
			hdr->e_ident[EI_MAG1] != ELFMAG1 &&
			hdr->e_ident[EI_MAG2] != ELFMAG2 &&
			hdr->e_ident[EI_MAG3] != ELFMAG3) {

		return EFI_UNSUPPORTED;
	}

	if (hdr->e_machine != EM_AARCH64) {
		return EFI_UNSUPPORTED;
	}

	if (hdr->e_ident[EI_CLASS] != ELFCLASS64) {
		return EFI_UNSUPPORTED;
	}

	if (hdr->e_ident[EI_DATA] != ELFDATALSB) {
		return EFI_UNSUPPORTED;
	}

	return EFI_SUCCESS;
}
