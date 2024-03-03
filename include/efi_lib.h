#ifndef EFI_LIB_H
#define EFI_LIB_H


#include <efi_def.h>
#include <efi_api.h>



extern efi_system_table_t 		*ST;
extern efi_boot_services_t		*BS;
extern efi_runtime_services_t	*RT;

extern efi_text_input_proto_t	*stdin;
extern efi_text_output_proto_t	*stdout;
extern efi_text_output_proto_t	*stderr;







void initialize_libs(efi_handle_t img_handle, efi_system_table_t *sys_tbl);
int32_t guidcmp(efi_guid_t *g1, efi_guid_t *g2);
efi_status_t is_digit(char16_t ch);
efi_status_t is_alpha(char16_t ch);
void tolower(char16_t *s);
void toupper(char16_t *s);
void putc(char16_t ch);
void puts(char16_t *string);
void clear_screen(void);
void sleep(uint64_t	seconds);
void *alloc(uint64_t length);
void *alloc_page(void);
void *alloc_pages(uint64_t length);
void free(void *buf);
void memcpy(void *dest, void *source, uint64_t length);
void memset(void *buf, uint8_t val, uint64_t length);
efi_status_t memcmp(void *b, void *a, uint64_t length);
efi_status_t strcmp(char16_t *b, char16_t *a, uint64_t length);
uint64_t strlen(char16_t *s);
void strcpy(char16_t *dst, char16_t *s);
void strrev(char16_t *s, uint64_t length);
void strrep(char16_t *s, char16_t a, char16_t b);
void strcat(char16_t *buf, char16_t *s);
char16_t *itoa(int num, char16_t *buf, int base);
efi_status_t vprintf(char16_t *fmt, va_list args);
efi_status_t vsprintf(char16_t *buf, char16_t *fmt, va_list args);
efi_status_t printf(char16_t *fmt, ...);
efi_status_t sprintf(char16_t *buf, char16_t *fmt, ...);
efi_status_t get_file_info(efi_file_proto_t *fd, efi_file_info_t **info);
bool grow_buffer(efi_status_t *ret, void **buf, uint64_t length);
#endif
