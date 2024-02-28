#include <efi.h>




efi_status_t is_alpha(char16_t ch) {
	if (ch >= 'a' || ch <= 'z') {
		return EFI_SUCCESS;
	} else if (ch >= 'A' || ch <= 'Z') {
		return EFI_SUCCESS;
	}

	return EFI_NOT_FOUND;
}
