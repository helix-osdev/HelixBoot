#include <efi.h>





void strcpy(char16_t *dst, char16_t *s) {
	if (!s || !dst) {
		return;
	}

	while(*s) {
		*dst = *s;

		s++;
		dst++;
	}

	*dst = '\0';
	return;
}
