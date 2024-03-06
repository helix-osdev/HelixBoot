#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








elf64_phdr_t *elf_for_each_phdr(elf_fd_t *fd, uint64_t index) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_phdr_t *phdr = NULL;
	elf64_off_t offset = 0;


	offset = hdr->e_phoff + index * hdr->e_phentsize;
	phdr = elf_alloc(hdr->e_phentsize);

	if (!phdr) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	fseek(fd->elf_fd, offset);
	fread(fd->elf_fd, phdr, hdr->e_phentsize);

	return phdr;
}

efi_status_t elf_load_phdr(elf_fd_t *fd, elf64_phdr_t *phdr) {
	efi_status_t ret = 0;
	elf64_addr_t phys_base = 0, virt_base = 0;
	elf64_addr_t *segment;
	elf64_xword_t file_size = 0, segment_size = 0;
	elf64_xword_t segment_pages = 0;
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;



	switch(phdr->p_type) {
		case PT_LOAD:
			phys_base = phdr->p_paddr;
			virt_base = phdr->p_vaddr;

			if (phys_base <= 0x0 || virt_base <= 0x0) {
				// NULL segment
				return EFI_NOT_FOUND;
			}

			file_size = phdr->p_filesz;
			segment_size = phdr->p_memsz;
			segment_pages = EFI_SIZE_TO_PAGES(segment_size);
			segment = (elf64_addr_t *)phys_base;

			// Read program header into it's physical
			// address space
			fseek(fd->elf_fd, phdr->p_offset);
			fread(fd->elf_fd, (elf64_addr_t *)segment, phdr->p_filesz);

			break;
	}

	return EFI_SUCCESS;
}
