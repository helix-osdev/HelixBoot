#include <efi.h>
#include <devices/disk.h>




efi_file_info_t *get_file_info(efi_file_proto_t *fd) {
	efi_status_t ret = 0;
	efi_file_info_t *info = NULL;
	uint64_t info_size = sizeof(efi_file_info_t);
	efi_guid_t info_guid = EFI_FILE_INFO_ID;



	if (!fd) {
		return NULL;
	}

	ret = fd->get_info(fd,
			&info_guid,
			&info_size,
			(void *)&info);

	if (EFI_ERROR(ret) || !info) {
		return NULL;
	}

	return info;
}
