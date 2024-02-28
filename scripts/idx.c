#include <stdio.h>
#include <stdint.h>





int main(void) {
	uint64_t buf[512];

	uint64_t pgd_virt = 0xffff000040405000;
	uint64_t pud_virt = 0xffff000040405200;
	uint64_t pmd_virt = 0xffff000040405400;

	uint64_t pgd_phys = (pgd_virt >> 30) & 0x1ff;
	uint64_t pud_phys = (pud_virt >> 21) & 0x1ff;
	uint64_t pmd_phys = (pmd_virt >> 12) & 0x1ff;

	printf("PGD = %08lX\n",
			(pgd_virt & ~(0xfffffffff000)));
	printf("PUD = %08lX\n",
			(pud_virt & ~(0xfffffffff000)));
	printf("PMD = %08lX\n",
			(pmd_virt & ~(0xfffffffff000)));

	return 0;
}
