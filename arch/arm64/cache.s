.section .text,"x"
.global __flush_cache_range





__flush_cache_range:
	stp x29, x30, [sp, #-16]!
	stp x0, x1, [sp, #-16]!
	stp x2, x3, [sp, #-16]!
	stp x4, x5, [sp, #-16]!

	// x0 -> base address
	// x1 -> length

	add x1, x1, x0

	mrs x2, ctr_el0
	ubfx x4, x2, #16, #4
	mov x3, #4
	lsl x3, x3, x4
	sub x4, x3, #1
	bic x4, x0, x4

__clean_dcache:
	dc cvau, x4
	add x4, x4, x3
	cmp x4, x1
	blt __clean_dcache
	dsb ish

	and x2, x2, #0xF
	mov x3, #4
	lsl x3, x3, x2
	sub x4, x3, #1
	bic x4, x0, x4

__clean_icache:
	ic ivau, x4
	add x4, x4, x3
	cmp x4, x1
	blt __clean_icache
	dsb ish
	isb

	ldp x4, x5, [sp], #16
	ldp x2, x3, [sp], #16
	ldp x0, x1, [sp], #16
	ldp x29, x30, [sp], #16
	ret
