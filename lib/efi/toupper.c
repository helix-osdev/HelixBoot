#include <efi.h>




void toupper(char16_t *s) {
	if (!s) {
		return;
	}

	while(*s != '\0') {
		if (*s >= 'a' && *s <= 'z') {
			*s = *s - ('a' - 'A');
		}

		s++;
	}
}
