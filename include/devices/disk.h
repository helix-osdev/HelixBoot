#ifndef DISK_H
#define DISK_H

#include <efi.h>


extern efi_file_proto_t *efi_root;




uint64_t get_image_base(void);
uint64_t get_image_size(void);
efi_status_t get_boot_vol(efi_handle_t img_handle);
efi_file_proto_t *fopen(char16_t *name);
efi_status_t fclose(efi_file_proto_t *fd);
efi_status_t fseek(efi_file_proto_t *fd, uint64_t offset);
efi_status_t fread(efi_file_proto_t *fd, void *buf, uint64_t length);
efi_status_t fwrite(efi_file_proto_t *fd, void *buf, uint64_t length);

#endif
