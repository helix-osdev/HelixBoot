#include <efi.h>






efi_status_t vsprintf(char16_t *buf, char16_t *fmt, va_list args) {
	efi_status_t ret = 0;
	uint64_t i = 0, string_size = strlen(fmt);

	while(*fmt != '\0' && i < string_size) {
		if (*fmt == '%') {
			fmt++;

			switch(*fmt) {
				case 'c':
					buf[i] = va_arg(args, int);
					buf[i + 1] = '\0';

					i++;
					fmt++;
					break;

				case 's':
					char16_t *s = va_arg(args, char16_t*);
					i++;
					fmt++;
					break;

				case 'i':
				case 'd':
					int32_t s2 = va_arg(args, int32_t);

					itoa(s2, buf, 10);
					i++;
					fmt++;
					break;

				case 'u':
					uint64_t s3 = va_arg(args, uint64_t);

					itoa(s3, buf, 10);
					i++;
					fmt++;
					break;

				case 'b':
					uint64_t s4 = va_arg(args, uint64_t);

					itoa(s4, buf, 2);
					i++;
					fmt++;
					break;

				case 'o':
					uint64_t s5 = va_arg(args, uint64_t);

					itoa(s5, buf, 8);
					i++;
					fmt++;
					break;

				case 'x':
				case 'X':
					uint64_t s6 = va_arg(args, uint64_t);

					itoa(s6, buf, 16);
					i++;
					fmt++;
					break;

				default:
					i++;
					fmt++;
					break;
					
			}

		} else {
			buf[i] = *fmt;
			buf[i + 1] = '\0';

			i++;
			fmt++;
		}
	}

	return ret;
}
