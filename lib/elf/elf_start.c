#include <efi.h>
#include <elf/elf.h>
#include <bootinfo.h>





void elf_exec(elf_fd_t *fd, bootinfo_t *info) {
	void (*exec)(bootinfo_t *boot_info);

	// Set entry point
	exec = (void *)fd->elf_hdr->e_entry;

	// Execute ELF
	exec(info);
}
