#include <efi.h>





void *malloc(uint64_t length) {
	efi_status_t ret = 0;
	void *buf = NULL;

	if (length <= 0) {
		return NULL;
	}

	ret = BS->allocate_pool(EfiLoaderData,
			length,
			(void *)&buf);

	if (EFI_ERROR(ret) && !buf) {
		return NULL;
	}

	return buf;
}
