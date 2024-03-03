#include <efi.h>
#include <devices/disk.h>



// Global handle for EFI partition
efi_file_proto_t *efi_root = NULL;

static uint64_t image_base = 0;
static uint64_t image_size = 0;




uint64_t get_image_base(void) {
	return image_base;
}

uint64_t get_image_size(void) {
	return image_size;
}

efi_status_t get_boot_vol(efi_handle_t img_handle) {
	efi_status_t ret = 0;
	efi_guid_t img_guid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
	efi_guid_t dev_guid = EFI_DEVICE_PATH_PROTOCOL_GUID;
	efi_loaded_image_proto_t *img_load = NULL;
	efi_device_path_proto_t *dev_path = NULL;
	efi_guid_t fs_guid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
	efi_filesystem_proto_t *volume = NULL;



	ret = BS->handle_protocol(img_handle,
			&img_guid,
			(void **)&img_load);

	if (EFI_ERROR(ret)) {
		printf(L"Failed to get EFI handle protocol! (%r)\n", ret);
		return ret;
	}

	ret = BS->handle_protocol(img_load->device_path,
			&dev_guid,
			(void **)&dev_path);

	if (EFI_ERROR(ret)) {
		printf(L"Failed to get EFI device path! (%r)\n", ret);
		return ret;
	}

	ret = BS->handle_protocol(img_load->device_path,
			&fs_guid,
			(void **)&volume);

	if (EFI_ERROR(ret)) {
		printf(L"Failed to get EFI FS volume! (%r)\n", ret);
		return ret;
	}

	ret = volume->open_volume(volume, &efi_root);

	if (EFI_ERROR(ret)) {
		printf(L"Failed to mount EFI partition! (%r)\n", ret);
		return ret;
	}

	image_base = (uint64_t)img_load->image_base;
	image_size = (uint64_t)img_load->image_size;

	return EFI_SUCCESS;
}

efi_file_proto_t *fopen(char16_t *name) {
	efi_status_t ret = 0;
	efi_file_proto_t *fd = NULL;


	if (!name) {
		return NULL;
	}

	ret = efi_root->open(efi_root,
			&fd,
			name,
			EFI_FILE_MODE_READ |
			EFI_FILE_MODE_WRITE,
			0);

	if (EFI_ERROR(ret)) {
		return NULL;
	}

	return fd;
}

efi_status_t fclose(efi_file_proto_t *fd) {
	efi_status_t ret = 0;


	ret = fd->close(fd);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t fseek(efi_file_proto_t *fd, uint64_t offset) {
	efi_status_t ret = 0;


	ret = fd->set_position(fd, offset);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t fread(efi_file_proto_t *fd, void *buf, uint64_t length) {
	efi_status_t ret = 0;


	ret = fd->read(fd, &length, buf);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}

efi_status_t fwrite(efi_file_proto_t *fd, void *buf, uint64_t length) {
	efi_status_t ret = 0;

	ret = fd->write(fd, length, buf);

	if (EFI_ERROR(ret)) {
		return ret;
	}

	return EFI_SUCCESS;
}
