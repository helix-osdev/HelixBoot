#include <efi.h>
#include <devices/uart.h>



efi_system_table_t		*ST;
efi_boot_services_t		*BS;
efi_runtime_services_t	*RT;

efi_text_input_proto_t	*stdin;
efi_text_output_proto_t	*stdout;
efi_text_output_proto_t	*stderr;




void initialize_libs(efi_handle_t img_handle,
		efi_system_table_t *sys_tbl) {
	(void)img_handle;

	// Setup global pointers
	ST = sys_tbl;
	BS = sys_tbl->boot_services;
	RT = sys_tbl->runtime_services;

	stdin = ST->con_in;
	stdout = ST->con_out;
	stderr = ST->stderror;
}

void clear_screen(void) {
	stdout->clear_screen(stdout);
}
