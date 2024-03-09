#ifndef ELF_API_H
#define ELF_API_H

#include <efi.h>
#include <bootinfo.h>
#include <elf/elf_def.h>





elf_fd_t *elf_open(char16_t *name);
void elf_close(elf_fd_t *fd);
efi_status_t elf_check(elf_fd_t *fd);
efi_status_t elf_load(elf_fd_t *fd);
void elf_exec(elf_fd_t *fd, bootinfo_t *info);

elf64_shdr_t *elf_for_each_shdr(elf_fd_t *fd, elf64_xword_t index);
elf64_phdr_t *elf_for_each_phdr(elf_fd_t *fd, elf64_xword_t index);

efi_status_t elf_load_phdr(elf_fd_t *fd, elf64_phdr_t *phdr);
efi_status_t elf_load_dynamic_phdr(elf_fd_t *fd, elf64_phdr_t *phdr);
efi_status_t elf_load_shdr(elf_fd_t *fd, elf64_shdr_t *shdr);

#endif
