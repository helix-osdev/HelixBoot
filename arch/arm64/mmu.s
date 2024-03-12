.section .text,"x"
.global __map_table_entry


__map_table_entry:
	stp x29, x30, [sp, #-16]!

	// x0 -> page table
	// x1 -> virtual address
	// x2 -> table shift
	// x3 -> flags

	// Preserve registers we're about to clobber
	stp x4, x5, [sp, #-16]!
	stp x6, x7, [sp, #-16]!

	// Get entry index
	lsr x5, x1, x2
	lsl x5, x5, #3

	// ORR the desired flags and store into the page
	// table at the calculated index
	orr x1, x1, x3
	str x1, [x0, x5]

	// Restore clobbered registers
	ldp x6, x7, [sp], #16
	ldp x4, x5, [sp], #16
	ldp x29, x30, [sp], #16
	ret
