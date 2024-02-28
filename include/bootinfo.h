#ifndef BOOTINFO_H
#define BOOTINFO_H

#include <efi.h>
#include <mm/mm.h>


typedef struct {
	uint64_t		ram_base;
	uint64_t		ram_size;
} __attribute__((packed)) bootinfo_t;

#endif
