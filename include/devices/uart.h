#ifndef UART_H
#define UART_H

#include <efi.h>


#define UART_BASE	0x09000000

#define UART_CTS	(1UL << 0UL)
#define UART_DSR	(1UL << 1UL)
#define UART_DCD	(1UL << 2UL)
#define UART_BUSY	(1UL << 3UL)
#define UART_RXFE	(1UL << 4UL)
#define UART_TXFF	(1UL << 5UL)
#define UART_RXFF	(1UL << 6UL)
#define UART_TXFE	(1UL << 7UL)
#define UART_RI		(1UL << 8UL)

#define LCRH_FEN        (1 << 4u)
#define LCRH_PEN        (1 << 1u)
#define LCRH_EPS        (1 << 2u)
#define LCRH_STP2       (1 << 3u)
#define LCRH_SPS        (1 << 7u)
#define CR_UARTEN       (1 << 0u)

#define LCRH_WLEN_5BITS (0u << 5u)
#define LCRH_WLEN_6BITS (1u << 5u)
#define LCRH_WLEN_7BITS (2u << 5u)
#define LCRH_WLEN_8BITS (3u << 5u)





typedef struct {
	bool		parity;
	uint32_t	baudrate;
	uint32_t	data_bits;
	uint32_t	stop_bits;
} uart_config_t;

typedef struct {
	uint32_t	uart_dr;
	uint32_t	uart_rsr;
	uint32_t	__unused[4];
	uint32_t	uart_fr;
	uint32_t	__unused2;
	uint32_t	uart_ilpr;
	uint32_t	uart_ibrd;
	uint32_t	uart_fbrd;
	uint32_t	uart_lcrh;
	uint32_t	uart_cr;
	uint32_t	uart_ifls;
	uint32_t	uart_imsc;
	uint32_t	uart_ris;
	uint32_t	uart_mis;
	uint32_t	uart_icr;
	uint32_t	uart_macr;
} __attribute__((packed)) pl011_t;



int uart_init(uart_config_t *cfg);
void uart_putc(char16_t c);
void uart_puts(char16_t *s);

#endif
