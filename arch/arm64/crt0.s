.section .text,"x"
.global efi_main




efi_main:
	mov x29, xzr
	mov x30, xzr

	// x0 -> EFI image handle
	// x1 -> EFI system table

	// Start main routine
	b helix_main

halt:
	wfi
	b halt


