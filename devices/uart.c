#include <efi.h>
#include <devices/uart.h>


static volatile pl011_t *uart0 = (pl011_t *)UART_BASE;
static uint64_t ref_clock = 24000000UL;





int uart_init(uart_config_t *cfg) {
	if (cfg->data_bits < 5 || cfg->data_bits > 8) {
		return -1;
	}

	if (cfg->stop_bits < 0 || cfg->stop_bits > 2) {
		return -1;
	}

	uart0->uart_cr &= ~CR_UARTEN;

	while(uart0->uart_fr & UART_BUSY);
	uart0->uart_lcrh &= ~LCRH_FEN;

	uint32_t ibrd = 0, fbrd = 0;
	uint32_t div = 4 * ref_clock / cfg->baudrate;

	fbrd = div & 0x3f;
	ibrd = (div >> 6) & 0xffff;

	uart0->uart_ibrd = ibrd;
	uart0->uart_fbrd = fbrd;

	uint32_t lcrh = LCRH_WLEN_8BITS;

	lcrh &= ~LCRH_PEN;
    lcrh &= ~LCRH_EPS;
    lcrh &= ~LCRH_SPS;
	lcrh &= ~LCRH_STP2;
	lcrh |= LCRH_FEN;

	uart0->uart_lcrh = lcrh;

	uart0->uart_cr |= CR_UARTEN;
	return 0;
}

void uart_putc(char16_t c) {
	while(uart0->uart_fr & UART_TXFF);
	uart0->uart_dr = c;
}

void uart_puts(char16_t *s) {
	while(*s != '\0') {
		uart_putc(*s);
		s++;
	}
}
