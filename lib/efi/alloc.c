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

	return buf;
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

	return buf;
}

bool grow_buffer(efi_status_t *ret, void **buf, uint64_t length) {
	bool retry = false;

	if (!*buf && length) {
		*ret = EFI_BUFFER_TOO_SMALL;
	}

	if (*ret == EFI_BUFFER_TOO_SMALL) {
		if (*buf) {
			free(*buf);
		}

		*buf = alloc(length);

		if (*buf) {
			retry = true;
		} else {
			*ret = EFI_OUT_OF_RESOURCES;
		}
	}

	if (!retry && EFI_ERROR(*ret) && *buf) {
		free(*buf);
		*buf = NULL;
	}

	return retry;
}
