#ifndef PAGING_H
#define PAGING_H




#define MAX_PT_SIZE 512

#define L0_SHIFT	39
#define L1_SHIFT	30
#define L2_SHIFT	21
#define L3_SHIFT	12

#define BLOCK_SHIFT		L1_SHIFT
#define BLOCK_SIZE		(1UL << BLOCK_SHIFT)
#define BLOCK_MASK		(~(BLOCK_SIZE - 1))

#define SECTION_SHIFT 	L2_SHIFT
#define SECTION_SIZE	(1UL << SECTION_SHIFT)
#define SECTION_MASK	(~(SECTION_SIZE - 1))

#define PAGE_SHIFT		L3_SHIFT
#define PAGE_SIZE		(1UL << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))

#define PT_FAULT	0x0
#define PT_VALID	(1UL << 0UL)
#define PT_TABLE	(1UL << 3UL)
#define PT_BLOCK	(1UL << 1UL)

#define PT_NORMAL_WBWA		0x405
#define PT_DEVICE_nGnRnE	0x409

#define PT_NS		(1UL << 5UL)
#define PT_SE		(2UL << 5UL)

#define PT_AP_NO_EL0	(0UL << 6UL)
#define PT_AP_ALL_EL	(1UL << 6UL)
#define PT_AP_NO_EL0_RO	(2UL << 6UL)
#define PT_AP_ALL_EL_RO	(3UL << 6UL)
#define PT_AP_RW		(4UL << 6UL)
#define PT_AP_RO		(5UL << 6UL)

#define PT_SH_NS	(0UL << 8UL)
#define PT_SH_OS	(1UL << 8UL)
#define PT_SH_IS	(2UL << 8UL)

#define PT_AF		(1UL << 10UL)
#define PT_NG		(1UL << 11UL)

#define PT_CON		(1ULL << 52ULL)
#define PT_PNX		(1ULL << 53ULL)
#define PT_UNX		(1ULL << 54ULL)

#define PT_KERNEL	(1ULL << 63ULL)






efi_status_t paging_init(efi_memory_map_t *m);

void map_page(uint64_t vaddr, uint64_t paddr, uint64_t length, uint64_t attrs);

void mmu_enable(void);
void mmu_disable(void);

void flush_cache_range(uint64_t base_addr, uint64_t length);

void update_page_tables(void);

#endif
