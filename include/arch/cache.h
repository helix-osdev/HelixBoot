#ifndef CACHE_H
#define CACHE_H

#include <efi.h>

extern void __flush_cache_range(uint64_t base_addr, uint64_t length);

#endif
