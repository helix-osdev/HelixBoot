#include <efi.h>




void tolower(char16_t *s) {
	if (!s) {
		return;
	}

	while(*s != '\0') {
		if (*s >= 'A' && *s <= 'Z') {
			*s = *s - ('A' - 'a');
		}

		s++;
	}
}
