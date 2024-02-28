#include <stdio.h>
#include <stdint.h>





int main(void) {
	uint64_t vaddr = 0xffff000000000000;
	uint64_t paddr = 0x40300000;

	uint64_t n = vaddr | paddr;

	printf("N = 0x%08lX\n", n & 0xfffffffff000);

	return 0;
}
