#ifndef BOOTINFO_H
#define BOOTINFO_H

#include <efi.h>
#include <mm/mm.h>


typedef struct {
	efi_memory_map_t			*mm;
	efi_runtime_services_t		*RT;
} __attribute__((packed)) bootinfo_t;

#endif
