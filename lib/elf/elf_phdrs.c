#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








elf64_phdr_t *elf_for_each_phdr(elf_fd_t *fd, uint64_t index) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_phdr_t *phdr = NULL;
	uint64_t offset = 0;


	offset = hdr->e_phoff + index * hdr->e_phentsize;
	phdr = alloc(hdr->e_phentsize);

	if (!phdr) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	fseek(fd->elf_fd, offset);
	fread(fd->elf_fd, phdr, hdr->e_phentsize);

	return phdr;
}
