#include <efi.h>





void memset(void *buf, uint8_t val, uint64_t length) {
	uint8_t *ptr = (uint8_t *)buf;

	for (uint64_t i = 0; i < length; i++) {
		ptr[i] = val;
	}
}
