#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>








elf64_shdr_t *elf_for_each_shdr(elf_fd_t *fd, uint64_t index) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_hdr;
	elf64_shdr_t *shdr = NULL;
	elf64_off_t offset = 0;


	offset = hdr->e_shoff + index * hdr->e_shentsize;
	shdr = elf_alloc(hdr->e_shentsize);

	if (!shdr) {
		printf(L"elf: out of resources!\n");
		return NULL;
	}

	fseek(fd->elf_fd, offset);
	fread(fd->elf_fd, shdr, hdr->e_shentsize);

	return shdr;
}
