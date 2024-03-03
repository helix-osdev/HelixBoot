#include <efi.h>
#include <devices/disk.h>





efi_file_info_t *get_file_info(efi_file_proto_t *fd) {
	efi_status_t ret = 0;
	efi_file_info_t *info = NULL;
	uint64_t info_size = SIZE_OF_EFI_FILE_INFO + 200;
	efi_guid_t info_guid = EFI_FILE_INFO_ID;


	while(grow_buffer(&ret, (void **)&info, info_size)) {
		ret = fd->get_info(fd,
				&info_guid,
				&info_size,
				info);
	}

	return info;
}
