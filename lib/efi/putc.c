#include <efi.h>
#include <devices/uart.h>





void putc(char16_t ch) {
	char16_t buf[2];

	buf[0] = ch;
	buf[1] = '\0';

	uart_puts(buf);
}
