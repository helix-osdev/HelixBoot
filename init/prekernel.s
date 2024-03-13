.section .text,"x"
.global __kernel_exec


.equ KERNEL_LOAD_ADDR,	0x00
.equ KERNEL_LOAD_SIZE,	0x08
.equ RAM_BASE_ADDR,		0x10
.equ RAM_BASE_SIZE,		0x18
.equ EFI_MEM_MAP_ADDR,	0x20


__kernel_exec:
	mov x29, xzr
	mov x30, xzr

	// x0 -> boot_info struct
