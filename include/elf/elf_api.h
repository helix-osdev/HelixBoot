#ifndef ELF_API_H
#define ELF_API_H

#include <efi.h>
#include <elf/elf_def.h>





elf_fd_t *elf_open(char16_t *name);
void elf_close(elf_fd_t *fd);
efi_status_t elf_check(void *buf);

uint64_t elf_shdr_size(void *buf);

#endif
