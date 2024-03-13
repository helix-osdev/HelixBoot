#include <efi.h>
#include <mm/mm.h>
#include <elf/elf.h>
#include <arch/asm.h>
#include <bootinfo.h>
#include <devices/disk.h>
#include <devices/uart.h>






efi_status_t helix_main(efi_handle_t img_handle, efi_system_table_t *sys_tbl) {
	elf_fd_t *fd = NULL;
	efi_memory_map_t m;
	bootinfo_t boot_info;

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

	get_memory_map(&m);
	get_boot_vol(img_handle);

	printf(L"Loading kernel...\n");
	fd = elf_open(L"\\HelixOS\\kernel.elf");
	elf_load(fd);

	printf(L"Exiting boot services...\n");
	exit_boot_services(img_handle, &m);

	// Populate boot info data for kernel use. Do this
	// here to ensure we exit boot services without issue
	boot_info.mm = &m;

	while(1);
}
