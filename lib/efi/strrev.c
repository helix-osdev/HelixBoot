#include <efi.h>




void strrev(char16_t *s, uint64_t length) {
	uint64_t start = 0, end = length - 1;

	while(start < end) {
		char16_t tmp = s[start];

		s[start] = s[end];
		s[end] = tmp;

		start++;
		end--;
	}
}
