#include <efi.h>
#include <elf/elf.h>






bool elf_validate(elf_fd_t *fd) {
	if (fd->elf_hdr->e_ident[EI_MAG0] != ELFMAG0 &&
			fd->elf_hdr->e_ident[EI_MAG1] != ELFMAG1 &&
			fd->elf_hdr->e_ident[EI_MAG2] != ELFMAG2 &&
			fd->elf_hdr->e_ident[EI_MAG3] != ELFMAG3) {

		return false;
	}

	return true;
}

bool elf_is_supported_arch(elf_fd_t *fd) {
	if (fd->elf_hdr->e_ident[EI_CLASS] != ELFCLASS64) {
		return false;
	}

	if (fd->elf_hdr->e_ident[EI_DATA] != ELFDATALSB) {
		return false;
	}

	if (fd->elf_hdr->e_machine != EM_AARCH64) {
		return false;
	}

	return true;
}
