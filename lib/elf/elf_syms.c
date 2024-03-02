#include <efi.h>
#include <elf/elf.h>






static uint64_t elf_get_str_table_offset(elf_fd_t *fd) {
	uint64_t offset = 0;


	offset = fd->elf_hdr->e_shoff + fd->elf_hdr->e_shstrndx * fd->elf_hdr->e_shentsize;

	return offset;
}

char *elf_get_str_table(elf_fd_t *fd) {
	char *str_table = NULL;
	uint64_t table_offset = 0, table_size = 0;

	
	table_offset = elf_get_str_table_offset(fd);
	table_size = fd->shdrs[table_offset].sh_size;
	str_table = alloc(table_size);

	if (!str_table) {
		return EFI_OUT_OF_RESOURCES;
	}

	fseek(fd->elf_fd, fd->shdrs[table_offset].sh_offset);
	fread(fd->elf_fd, str_table, table_size);

	return str_table;
}
