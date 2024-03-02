#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






static uint64_t elf_get_phdr_size(elf_fd_t *fd) {
	uint64_t phdr_size = 0;

	if (!fd || !fd->elf_hdr) {
		return EFI_NOT_FOUND;
	}

	phdr_size = fd->elf_hdr->e_phnum * fd->elf_hdr->e_phentsize;
	return phdr_size;
}

static elf64_phdr_t *elf_for_each_phdr(elf_fd_t *fd, uint64_t idx) {
	elf64_phdr_t *phdr = NULL;

	phdr = (elf64_phdr_t *)&fd->phdrs[idx];

	return phdr;
}

efi_status_t elf_load_phdrs(elf_fd_t *fd) {
	efi_status_t ret = 0;
	uint64_t phdr_size = 0, i = 0;



	phdr_size = elf_get_phdr_size(fd);
	fd->phdrs = alloc(phdr_size);

	if (!fd->phdrs) {
		return EFI_OUT_OF_RESOURCES;
	}

	fseek(fd->elf_fd, fd->elf_hdr->e_phoff);
	fread(fd->elf_fd, fd->phdrs, phdr_size);

	for (i = 0; i < fd->elf_hdr->e_phnum; i++) {
		elf64_phdr_t *phdr = elf_for_each_phdr(fd, i);

		if (phdr->p_type != PT_LOAD) {
			// Only handle program headers
			continue;
		}

		// Only load executables by their virtual
		// address. Pages will be allocated to
		// satisfy requirments in UEFI since everything
		// is identity-mapped

		uint64_t virt_base = phdr->p_vaddr;
		uint64_t virt_mask = 0xfffffffff000;
		uint64_t phys_base = virt_base & virt_mask;
		uint64_t phys_segment = phys_base;

		if (phdr->p_vaddr <= 0xffff000000000000) {
			// Non-loadable segment
			continue;
		}

		phys_segment = (uint64_t)alloc_pages(phdr->p_filesz);	

		fseek(fd->elf_fd, phdr->p_offset);
		fread(fd->elf_fd, (uint64_t *)phys_segment, phdr->p_filesz);

		if (phdr->p_filesz < phdr->p_memsz) {
			uint64_t off = phdr->p_filesz;
			uint64_t diff = phdr->p_memsz - phdr->p_filesz;

			memset((uint64_t *)phys_segment + off, 0, diff);
		}
	}

	return EFI_SUCCESS;
}
