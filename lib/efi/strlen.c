#include <efi.h>





uint64_t strlen(char16_t *s) {
	uint64_t size = 0;

	while(*s != '\0') {
		size++;
		s++;
	}

	return size;
}
