#include <efi.h>
#include <mm/mm.h>
#include <mm/paging.h>
#include <arch/asm.h>
#include <arch/cache.h>
#include <devices/disk.h>




static uint64_t *l0;
static uint64_t *l1;
static uint64_t *l2;
static uint64_t *l3;







efi_status_t paging_init(efi_memory_map_t *m) {
	efi_status_t ret = 0;
	efi_memory_descriptor_t *md = NULL;
	uint64_t ram_base = 0, ram_size = 0;
	uint64_t pt_base = 0;



	if (!m) {
		return EFI_OUT_OF_RESOURCES;
	}	

	for (uint64_t i = 0; i < m->max_entries; i++) {
		md = for_each_desc(m, i);

		switch(md->type) {
			case EfiConventionalMemory:
				if (ram_base == 0) {
					// RAM base address
					ram_base = md->physical_start;
				}

				// Get all available conventional memory
				ram_size += md->number_of_pages * 4096;
				break;

			default:
				break;
		}
	}

	// Place new tables somewhere at the end of the free
	// conventional memory region. This is so we don't
	// overwrite the kernel or any potential modules or
	// ramdisk that was previously loaded
	pt_base = ram_base + ram_size - 0x1000;

	l1 = (uint64_t *)pt_base;
	l2 = (uint64_t *)(pt_base + 0x200);
	l3 = (uint64_t *)(pt_base + 0x400);

	memset(l1, 0, 0x200);
	memset(l2, 0, 0x200);
	memset(l3, 0, 0x200);

	uint64_t rom_idx = (0x00000000 >> L1_SHIFT) & 0x1ff;

	l1[rom_idx] = 0x00000000;
	l1[rom_idx] |= PT_VALID | PT_AF | PT_DEVICE_nGnRnE | PT_AP_RW;

	uint64_t ram_idx = (0x40000000 >> L1_SHIFT) & 0x1ff;

	l1[ram_idx] = 0x40000000;
	l1[ram_idx] |= PT_VALID | PT_AF | PT_AP_RW;

	// Flush ROM region
	flush_cache_range(0x00000000, 0x40000000);

	// Flush free RAM region
	flush_cache_range(ram_base, ram_size);

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

void update_page_tables(void) {
	set_ttbr0((uint64_t)l1);
	set_ttbr1((uint64_t)l1);
}
