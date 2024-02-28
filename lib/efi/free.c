#include <efi.h>




void free(void *buf) {
	if (buf) {
		BS->free_pool(buf);
	}
}
