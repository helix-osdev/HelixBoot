#include <efi.h>
#include <mm/mm.h>
#include <mm/paging.h>
#include <elf/elf.h>
#include <arch/asm.h>
#include <devices/disk.h>
#include <devices/uart.h>






efi_status_t helix_main(efi_handle_t img_handle, efi_system_table_t *sys_tbl) {
	elf_fd_t *fd = NULL;
	efi_memory_map_t m;

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
	fd = elf_open(L"kernel.elf");
	elf_load(fd);

	printf(L"Exiting boot services...\n");
	exit_boot_services(img_handle, &m);

	// Things from this point forward will be a bit
	// quick and dirty just to get the kernel into
	// virtual memory. I still can't get QEMU to play
	// nice with any paging setup so this *should* work
	// for the mean time

	printf(L"Updating page tables...\n");
	paging_init(&m);

	mmu_disable();
	isb();

	set_mair(0);
	set_tcr(0);
	set_ttbr0(0);
	set_ttbr1(0);
	dsb(sy);
	isb();

	set_mair(0xFF44);

	uint64_t tcr = 0x19;
	tcr |= TCR_IRGN0_WBWA;
	tcr |= TCR_ORGNO_WBWA;
	tcr |= TCR_SH0_ISH;
	tcr |= TCR_TG0_4K;

	tcr |= TCR_IRGN1_WBWA;
	tcr |= TCR_ORGN1_WBWA;
	tcr |= TCR_SH1_ISH;
	tcr |= TCR_TG1_4K;
	tcr |= TCR_EPD1_ENABLE;
	set_tcr(tcr);
	isb();

	tlbi(vmalle1);
	dsb(sy);
	isb();

	update_page_tables();
	mmu_enable();
	isb();

	printf(L"Done!\n");

	while(1);
}
