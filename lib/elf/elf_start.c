#include <efi.h>
#include <elf/elf.h>
#include <bootinfo.h>





void elf_exec(elf_fd_t *fd) {
	void (*exec)(void);

	printf(L"elf: starting %s...\n", fd->elf_info->file_name);

	// Set entry point
	exec = (void *)fd->elf_hdr->e_entry;

	// Execute ELF
	exec();
}
