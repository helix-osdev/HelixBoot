#include <efi.h>





efi_status_t strcmp(char16_t *b, char16_t *a, uint64_t length) {
	efi_status_t ret = 0;

	for (uint64_t i = 0; i < length; i++) {
		if (a[i] > b[i]) {
			return EFI_NOT_FOUND;
		} else if (a[i] < b[i]) {
			return EFI_NOT_FOUND;
		}
	}

	return EFI_SUCCESS;
}
