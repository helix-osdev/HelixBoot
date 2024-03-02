#ifndef ELF_API_H
#define ELF_API_H

#include <efi.h>
#include <elf/elf_def.h>





elf_fd_t *elf_open(char16_t *name);
void elf_close(elf_fd_t *fd);
efi_status_t elf_load(elf_fd_t *fd);

bool elf_validate(elf_fd_t *fd);
bool elf_is_supported_arch(elf_fd_t *fd);

efi_status_t elf_load_phdrs(elf_fd_t *fd);

#endif
