.section .text, "x"


.global __read_sctlr
.global __set_sctlr

__read_sctlr:	
	mrs x0, sctlr_el1
	ret

__set_sctlr:
	msr sctlr_el1, x0
	ret


.global __read_ttbr0
.global __set_ttbr0

__read_ttbr0:
	mrs x0, ttbr0_el1
	ret

__set_ttbr0:
	msr ttbr0_el1, x0
	ret


.global __read_ttbr1
.global __set_ttbr1

__read_ttbr1:
	mrs x0, ttbr1_el1
	ret

__set_ttbr1:
	msr ttbr1_el1, x0
	ret


.global __read_mair
.global __set_mair

__read_mair:
	mrs x0, mair_el1
	ret

__set_mair:
	msr mair_el1, x0
	ret


.global __read_tcr
.global __set_tcr

__read_tcr:
	mrs x0, tcr_el1
	ret

__set_tcr:
	msr tcr_el1, x0
	ret
