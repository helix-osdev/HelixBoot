#ifndef KERNEL_H
#define KERNEL_H

#include <efi.h>
#include <bootinfo.h>


extern void __kernel_exec(bootinfo_t *info);

#endif
