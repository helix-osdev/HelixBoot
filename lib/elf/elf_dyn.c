#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








efi_status_t elf_load_dynamic_phdr(elf_fd_t *fd, elf64_phdr_t *phdr) {
	efi_status_t ret = 0;
	elf64_addr_t phys_base = 0, virt_base = 0;



	if (!phdr || !fd) {
		return EFI_OUT_OF_RESOURCES;
	}

	switch(phdr->p_type) {
		case PT_DYNAMIC:
			// Load segment
			break;
	}

	return EFI_SUCCESS;
}
