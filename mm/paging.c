#include <efi.h>
#include <mm/mm.h>
#include <mm/paging.h>

#include <arch/asm.h>
#include <arch/cache.h>




static uint64_t *pgd;
static uint64_t *pud;
static uint64_t *pmd;








efi_status_t paging_init(efi_memory_map_t *m) {
	efi_status_t ret = 0;
	efi_memory_descriptor_t *md = NULL;
	uint64_t ram_base = 0, ram_size = 0;
	uint64_t pt_base = 0;



	if (!m) {
		return EFI_OUT_OF_RESOURCES;
	}

	// Find RAM base to place new page tables
	for (uint64_t i = 0; i < m->max_entries; i++) {
		md = for_each_desc(m, i);

		switch(md->type) {
			case EfiConventionalMemory:
				// It will the first entry
				if (ram_base == 0) {
					ram_base = md->physical_start;
					ram_size = md->number_of_pages * 4096;
					pt_base = ram_base + ram_size - 65536;
				}

				break;

			default:
				break;
		}
	}

	// Place new tables somewhere at the end of the free
	// conventional memory region. This is so we don't
	// overwrite the kernel or any potential modules or
	// ramdisk that was previously loaded

	pgd = (uint64_t *)pt_base;
	pud = (uint64_t *)(pt_base + 0x200);
	pmd = (uint64_t *)(pt_base + 0x400);

	// Clean page tables
	memset(pgd, 0, 0x200);
	memset(pud, 0, 0x200);
	memset(pmd, 0, 0x200);

	return EFI_SUCCESS;
}

void mmu_enable(void) {
	uint64_t sctlr = 0;

	if (boot_services_exited == false) {
		printf(L"MM: can't modify MMU state while in boot services!\n");
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
		printf(L"MM: can't modify MMU state while in boot services!\n");
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