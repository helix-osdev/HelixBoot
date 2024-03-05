#include <efi.h>
#include <elf/elf.h>
#include <devices/disk.h>






void *elf_alloc(uint64_t length) {
	efi_status_t ret = 0;
	void *buf = NULL;


	ret = BS->allocate_pool(EfiRuntimeServicesData,
			length,
			(void *)&buf);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to allocate pool! (%r)\n", ret);
		return NULL;
	}

	return buf;
}

efi_status_t elf_alloc_addr(elf64_addr_t phys, uint64_t n_pages) {
	efi_status_t ret = 0;


	ret = BS->allocate_pages(AllocateAddress,
			EfiRuntimeServicesData,
			n_pages,
			(void *)&phys);

	if (EFI_ERROR(ret)) {
		printf(L"elf: failed to allocate address! (%r)\n", ret);
		return ret;
	}

	return EFI_SUCCESS;
}

void elf_free(void *buf) {
	if (buf) {
		free(buf);
	}
}
