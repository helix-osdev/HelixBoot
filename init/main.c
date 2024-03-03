#include <efi.h>
#include <mm/mm.h>
#include <elf/elf.h>
#include <devices/disk.h>
#include <devices/uart.h>






efi_status_t helix_main(efi_handle_t img_handle, efi_system_table_t *sys_tbl) {
	elf_fd_t *fd = NULL;

	initialize_libs(img_handle, sys_tbl);
	clear_screen();

	uart_config_t cfg = {
		.parity = false,
		.baudrate = 115200,
		.data_bits = 8,
		.stop_bits = 1
	};

	uart_init(&cfg);

	printf(L"Helix Bootloader v0.0.1\n");
	printf(L"Firmware vendor: %s\n", ST->firmware_vendor);

	get_boot_vol(img_handle);

	fd = elf_open(L"kernel.elf");

	while(1);
}
