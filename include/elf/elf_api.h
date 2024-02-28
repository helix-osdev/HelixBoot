#ifndef ELF_API_H
#define ELF_API_H

#include <efi.h>
#include <bootinfo.h>
#include <elf/elf_def.h>





elf_fd_t *elf_open(char16_t *name);
void elf_close(elf_fd_t *fd);
void elf_start(elf_fd_t *fd, bootinfo_t *info);
efi_status_t elf_load(elf_fd_t *fd);

#endif
