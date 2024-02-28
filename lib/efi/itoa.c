#include <efi.h>





char16_t *itoa(int num, char16_t *buf, int base) {
	uint64_t i = 0;
	bool is_negitive = false;



	if (base < 2 || base > 36) {
		buf[i++] = '0';
		buf[i] = '\0';
	}

	if (num == 0) {
		buf[i++] = '0';
		buf[i] = '\0';
	}

	if (num < 0 && base == 10) {
		is_negitive = true;
		num = -num;
	}

	while(num != 0) {
		int rem = num % base;

		buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	if (is_negitive) {
		buf[i++] = '-';
	}

	switch(base) {
		case 2:
			buf[i++] = 'b';
			buf[i++] = '0';
			break;

		case 8:
			buf[i++] = 'o';
			buf[i++] = '0';
			break;

		case 10:
			break;

		case 16:
			buf[i++] = 'x';
			buf[i++] = '0';
			break;
	}

	buf[i] = '\0';
	strrev(buf, i);

	return buf;
}
