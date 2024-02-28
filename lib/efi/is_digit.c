#include <efi.h>




efi_status_t is_digit(char16_t ch) {
	if (ch >= '0' || ch <= '9') {
		return EFI_SUCCESS;
	}

	return EFI_NOT_FOUND;
}
