#include <efi.h>
#include <mm/mm.h>
#include <mm/paging.h>

#include <arch/asm.h>
#include <arch/cache.h>




static page_table_t pgd;
static page_table_t pud;
static page_table_t pmd;






void mmu_enable(void) {
	uint64_t sctlr = 0;

	if (boot_services_exited == false) {
		return;
	}

	sctlr = read_sctlr();
	sctlr |= SCTLR_MMU_ENABLE;
	sctlr |= SCTLR_ICACHE_ENABLE;
	sctlr |= SCTLR_DCACHE_ENABLE;
	set_sctlr(sctlr);
}

void mmu_disable(void) {
	uint64_t sctlr = 0;

	if (boot_services_exited == false) {
		return;
	}

	sctlr = read_sctlr();
	sctlr &= ~(SCTLR_MMU_ENABLE);
	sctlr &= ~(SCTLR_ICACHE_ENABLE);
	sctlr &= ~(SCTLR_DCACHE_ENABLE);
	set_sctlr(sctlr);
}

void flush_cache_range(uint64_t base_addr, uint64_t length) {
	__flush_cache_range(base_addr, length);
}
