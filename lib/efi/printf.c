#include <efi.h>




efi_status_t printf(char16_t *fmt, ...) {
	efi_status_t ret = 0;
	va_list args;

	va_start(args, fmt);
	ret = vprintf(fmt, args);
	va_end(args);

	return ret;
}
