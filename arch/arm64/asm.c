#include <efi.h>
#include <arch/asm.h>




uint64_t read_sctlr(void) {
	uint64_t sctlr = 0;

	__asm__ volatile("mrs %0, sctlr_el1\n\t"
					 : "=r"(sctlr)
					 : : "x0");

	return sctlr;
}

void set_sctlr(uint64_t sctlr) {
	__asm__ volatile("msr sctlr_el1, %0\n\t"
					 : : "r"(sctlr)
					 : "x0");
}

uint64_t read_ttbr0(void) {
	uint64_t ttbr0 = 0;

	__asm__ volatile("mrs %0, ttbr0_el1\n\t"
					 : "=r"(ttbr0)
					 : : "x0");

	return ttbr0;
}

void set_ttbr0(uint64_t ttbr0) {
	__asm__ volatile("msr ttbr0_el1, %0\n\t"
					 : : "r"(ttbr0)
					 : "x0");
}

uint64_t read_ttbr1(void) {
	uint64_t ttbr1 = 0;

	__asm__ volatile("mrs %0, ttbr1_el1\n\t"
					 : "=r"(ttbr1)
					 : : "x0");

	return ttbr1;
}

void set_ttbr1(uint64_t ttbr1) {
	__asm__ volatile("msr ttbr1_el1, %0\n\t"
					 : : "r"(ttbr1)
					 : "x0");
}

uint64_t read_mair(void) {
	uint64_t mair = 0;

	__asm__ volatile("mrs %0, mair_el1\n\t"
					 : "=r"(mair)
					 : : "x0");

	return mair;
}

void set_mair(uint64_t mair) {
	__asm__ volatile("msr mair_el1, %0\n\t"
					 : : "r"(mair)
					 : "x0");
}

uint64_t read_tcr(void) {
	uint64_t tcr = 0;

	__asm__ volatile("mrs %0, tcr_el1\n\t"
					 : "=r"(tcr)
					 : : "x0");

	return tcr;
}

void set_tcr(uint64_t tcr) {
	__asm__ volatile("msr tcr_el1, %0\n\t"
					 : : "r"(tcr)
					 : "x0");
}
