#include <efi.h>





efi_status_t memcmp(void *b, void *a, uint64_t length) {
	efi_status_t ret = 0;
	
	uint8_t *_a = (uint8_t *)a;
	uint8_t *_b = (uint8_t *)b;

	for (uint64_t i = 0; i < length; i++) {
		if (_a[i] > _b[i]) {
			return EFI_NOT_FOUND;
		} else if (_a[i] < _b[i]) {
			return EFI_NOT_FOUND;
		}
	}

	return EFI_SUCCESS;
}
