#ifndef ELF_UTILS_H
#define ELF_UTILS_H


#include <efi.h>





void *elf_alloc(uint64_t length);
void elf_free(void *buf);
efi_status_t elf_alloc_addr(elf64_addr_t phys, uint64_t length);

#endif
