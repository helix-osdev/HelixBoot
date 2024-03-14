.section .text,"x"
.global __kernel_exec




__kernel_exec:
	mov x29, xzr
	mov x30, xzr

	// x0 -> bootinfo data struct

__halt:
	wfi
	b __halt
