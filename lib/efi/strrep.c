#include <efi.h>





void strrep(char16_t *s, char16_t a, char16_t b) {
	if (!s) {
		return;
	}

	while(*s != '\0') {
		if (*s == a) {
			*s = b;
		}

		s++;
	}
}
