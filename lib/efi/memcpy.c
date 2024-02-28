#include <efi.h>




void memcpy(void *dest, void *source, uint64_t length) {
	uint8_t *s = (uint8_t *)source;
	uint8_t *d = (uint8_t *)dest;


	for (uint64_t i = 0; i < length; i++) {
		d[i] = s[i];
	}
}
