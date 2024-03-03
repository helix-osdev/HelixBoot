#include <efi.h>
#include <elf/elf.h>






uint64_t elf_shdr_size(elf_fd_t *fd) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_data;
	uint64_t shdr_size = 0;

	shdr_size = hdr->e_shnum * hdr->e_shentsize;

	return shdr_size;
}

elf64_shdr_t *elf_get_shdr(elf_fd_t *fd) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_data;
	elf64_shdr_t *shdr = NULL;

	// Get first section header index
	shdr = (elf64_shdr_t *)(hdr + hdr->e_shoff);

	return shdr;
}

elf64_shdr_t *elf_for_each_shdr(elf_fd_t *fd, uint64_t idx) {
	elf64_ehdr_t *hdr = (elf64_ehdr_t *)fd->elf_data;
	elf64_shdr_t *shdr = NULL;
	uint64_t shdr_size = elf_shdr_size(fd);


	// Provide index to section header
	shdr = (elf64_shdr_t *)(hdr + hdr->e_shoff + idx * hdr->e_shentsize);

	return shdr;
}
