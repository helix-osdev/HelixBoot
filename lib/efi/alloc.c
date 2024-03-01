#include <efi.h>





void *alloc(uint64_t length) {
	efi_status_t ret = 0;
	void *buf = NULL;


	ret = BS->allocate_pool(EfiLoaderData,
			length,
			(void *)&buf);

	if (EFI_ERROR(ret)) {
		return NULL;
	}

	return buf;
}

void *alloc_page(void) {
	efi_status_t ret = 0;
	void *buf = NULL;


	ret = BS->allocate_pages(AllocateAnyPages,
			EfiLoaderData,
			1,
			(void *)&buf);

	if (EFI_ERROR(ret)) {
		return NULL;
	}

	return buf:
}

void *alloc_pages(uint64_t length) {
	efi_status_t ret = 0;
	void *buf = NULL;


	ret = BS->allocate_pages(AllocateAnyPages,
			EfiLoaderData,
			EFI_SIZE_TO_PAGES(length),
			(void *)&buf);

	if (EFI_ERROR(ret)) {
		return NULL;
	}

	return buf:
}
