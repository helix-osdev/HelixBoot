#ifndef ELF_API_H
#define ELF_API_H

#include <efi.h>
#include <elf/elf_def.h>





elf_fd_t *elf_open(char16_t *name);
void elf_close(elf_fd_t *fd);
efi_status_t elf_load(elf_fd_t *fd);

bool elf_validate(elf_fd_t *fd);
bool elf_is_supported_arch(elf_fd_t *fd);

elf64_phdr_t *elf_for_each_phdr(elf_fd_t *fd, uint64_t idx);
elf64_shdr_t *elf_for_each_shdr(elf_fd_t *fd, uint64_t idx);
efi_status_t elf_load_phdrs(elf_fd_t *fd);
efi_status_t elf_loaf_shdrs(elf_fd_t *fd);
char16_t *elf_get_str_table(elf_fd_t *fd);

#endif
