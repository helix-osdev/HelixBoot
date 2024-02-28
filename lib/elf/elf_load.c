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

static uint64_t elf_get_shdr_size(elf_fd_t *fd) {
	uint64_t shdr_size = 0;

	if (!fd || !fd->elf_hdr) {
		return EFI_NOT_FOUND;
	}

	shdr_size = fd->elf_hdr->e_shnum * fd->elf_hdr->e_shentsize;
	return shdr_size;
}


static efi_status_t elf_load_phdrs(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_phdr_t **phdrs = NULL;
	uint64_t phdr_size = 0, i = 0;

	phdr_size = elf_get_phdr_size(fd);
	phdrs = malloc(phdr_size);

	if (!phdrs) {
		return EFI_OUT_OF_RESOURCES;
	}

	fseek(fd->fd, fd->elf_hdr->e_phoff);
	fread(fd->fd, phdrs, phdr_size);

	for (i = 0; i < fd->elf_hdr->e_phnum; i++) {
		elf64_phdr_t *phdr = (elf64_phdr_t *)&phdrs[i];

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

		ret = BS->allocate_pages(AllocateAddress,
				EfiLoaderData,
				EFI_SIZE_TO_PAGES(phdr->p_memsz),
				(uint64_t *)&phys_segment);

		if (EFI_ERROR(ret)) {
			printf(L"Failed to allocate phys segment: %x! (%r)\n", phys_segment, ret);

			free(phdrs);
			return ret;
		}

		fseek(fd->fd, phdr->p_offset);
		fread(fd->fd, (uint64_t *)phys_segment, phdr->p_filesz);

		if (phdr->p_filesz < phdr->p_memsz) {
			uint64_t off = phdr->p_filesz;
			uint64_t diff = phdr->p_memsz - phdr->p_filesz;

			memset((uint64_t *)phys_segment + off, 0, diff);
		}

		printf(L"ELF: loaded segment %x\n", phys_segment);
	}

	free(phdrs);
	return EFI_SUCCESS;
}

efi_status_t elf_load(elf_fd_t *fd) {
	efi_status_t ret = 0;

	if (!fd->fd) {
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

	ret = elf_load_phdrs(fd);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}
