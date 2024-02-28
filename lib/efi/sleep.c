#include <efi.h>





void sleep(uint64_t seconds) {
	if (seconds <= 0) {
		return;
	}

	BS->stall(seconds * 1000 * 1000);
}
