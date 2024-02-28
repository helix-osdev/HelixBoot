#include <efi.h>
#include <devices/uart.h>





void puts(char16_t *string) {
	if (!string) {
		return;
	}

	uart_puts(string);
}
