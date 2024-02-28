#include <efi.h>
#include <elf/elf.h>
#include <bootinfo.h>
#include <devices/disk.h>




static bool elf_validate(elf_fd_t *fd) {
	if (fd->elf_hdr->e_ident[EI_MAG0] != ELFMAG0 &&
			fd->elf_hdr->e_ident[EI_MAG1] != ELFMAG1 &&
			fd->elf_hdr->e_ident[EI_MAG2] != ELFMAG2 &&
			fd->elf_hdr->e_ident[EI_MAG3] != ELFMAG3) {

		return false;
	}

	return true;
}

static bool elf_is_supported_arch(elf_fd_t *fd) {
	if (fd->elf_hdr->e_ident[EI_CLASS] != ELFCLASS64) {
		return false;
	}

	if (fd->elf_hdr->e_ident[EI_DATA] != ELFDATALSB) {
		return false;
	}

#ifdef ARM64
	if (fd->elf_hdr->e_machine != EM_AARCH64) {
		return false;
	}
#endif

#ifdef ARM
	if (fd->elf_hdr->e_machine != EM_ARM) {
		return false;
	}
#endif

	return true;
}

elf_fd_t *elf_open(char16_t *name) {
	elf_fd_t *elf = malloc(sizeof(elf_fd_t));

	elf->fd = fopen(name);
	elf->elf_hdr = malloc(sizeof(elf64_ehdr_t));

	if (!elf->fd) {
		printf(L"Failed to open %s\n", name);
		return NULL;
	}	

	fseek(elf->fd, 0);
	fread(elf->fd, elf->elf_hdr, sizeof(elf64_ehdr_t));

	// Validate that this is an ELF executable
	// otherwise reject it
	if (elf_validate(elf) == false) {
		printf(L"Non-ELF executable detected!\n");
		return NULL;
	}

	if (elf_is_supported_arch(elf) == false) {
		printf(L"ELF architecture not supported!\n");
		return NULL;
	}
	
	return elf;
}

void elf_close(elf_fd_t *fd) {
	// Don't free header since elf_start() relies on it
	// Memory can be reclaimed after ELF start. There
	// might be some cleaner way of doing this, but
	// for now it works

	if (fd) {
		if (fd->fd) {
			fclose(fd->fd);
		}
	}
}

void elf_start(elf_fd_t *fd, bootinfo_t *info) {
	uint64_t exec_addr = 0;
	void (*run)(bootinfo_t *info) = NULL;

	if (fd) {
		if (fd->elf_hdr) {
			// Set function pointer entry
			run = (void *)fd->elf_hdr->e_entry;
		}
	}

	if (run != NULL) {
		// Run application
		run(info);
	}
}

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

static bool elf_is_relocatable(elf64_phdr_t *p) {
	if (p->p_type != PT_DYNAMIC) {
		return false;
	}

	return true;
}

static efi_status_t elf_load_shdrs(elf_fd_t *fd) {
	efi_status_t ret = 0;
	elf64_shdr_t **shdrs = NULL;
	uint64_t shdr_size = 0;

	/*
	shdr_size = elf_get_shdr_size(fd);
	shdrs = malloc(shdr_size);

	if (!shdrs) {
		return EFI_OUT_OF_RESOURCES;
	}

	fseek(fd->fd, fd->elf_hdr->e_shoff);
	fread(fd->fd, shdrs, shdr_size);

	for (uint64_t i = 0; i < fd->elf_hdr->e_shnum; i++) {
		elf64_shdr_t *shdr = (elf64_shdr_t *)&shdrs[i];
	}

	free(shdrs);
	*/

	return EFI_SUCCESS;
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
