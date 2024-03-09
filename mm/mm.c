#include <efi.h>
#include <mm/mm.h>
#include <arch/asm.h>
#include <devices/disk.h>
#include <bootinfo.h>



bool boot_services_exited = false;






efi_memory_descriptor_t *for_each_desc(efi_memory_map_t *m, uint64_t idx) {
	efi_memory_descriptor_t *desc = NULL;

	desc = ((efi_memory_descriptor_t *)((uint64_t)m->map + (idx * m->desc_size)));

	return desc;
}

efi_status_t get_memory_map(efi_memory_map_t *m) {
	efi_status_t ret = 0;
	uint64_t map_size = 0, map_key, desc_size;
	uint32_t desc_ver;
	efi_memory_descriptor_t *map = NULL, *md = NULL;





	if (boot_services_exited == true) {
		printf(L"Can't get memory map after boot service exit!\n");
		return EFI_UNSUPPORTED;
	}

	// First call is to get buffer and descriptor size
	ret = BS->get_memory_map(&map_size,
			map,
			&map_key,
			&desc_size,
			&desc_ver);

	if (EFI_ERROR(ret) && ret != EFI_BUFFER_TOO_SMALL) {
		printf(L"Failed to get map descriptor size! (%r)\n", ret);
		return ret;
	}

	while(grow_buffer(&ret, (void **)&map, map_size)) {
		ret = BS->get_memory_map(&map_size,
				map,
				&map_key,
				&desc_size,
				&desc_ver);
	}

	if (EFI_ERROR(ret)) {
		printf(L"Failed to get memory map! (%r)\n", ret);
		return ret;
	}

	// Update memory map details
	m->map_size = map_size;
	m->map_key = map_key;
	m->desc_size = desc_size;
	m->desc_version = desc_ver;
	m->map = map;
	m->max_entries = (map_size / desc_size);

	return EFI_SUCCESS;
}

efi_status_t exit_boot_services(efi_handle_t img_handle, efi_memory_map_t *m) {
	efi_status_t ret = 0;
	uint64_t map_size = 0, map_key, desc_size;
	uint32_t desc_ver;
	efi_memory_descriptor_t *map = NULL;



	
	if (boot_services_exited == true) {
		printf(L"Boot services already exited!\n");
		return EFI_UNSUPPORTED;
	}

	// Retrive memory map details
	map_size = m->map_size;
	map_key = m->map_key;
	desc_size = m->desc_size;
	desc_ver = m->desc_version;
	map = m->map;
	
	// NOTE:
	// After memory allocations have been done this will
	// cause the map size to grow. We'll need to grow
	// buffer before we can exit the boot services
	ret = BS->get_memory_map(&map_size,
			map,
			&map_key,
			&desc_size,
			&desc_ver);

	if (EFI_ERROR(ret) && ret != EFI_BUFFER_TOO_SMALL) {
		printf(L"Failed to finalize memory map! (%r)\n", ret);
		boot_services_exited = false;
		return ret;
	}

	while(grow_buffer(&ret, (void **)&map, map_size)) {
		ret = BS->get_memory_map(&map_size,
				map,
				&map_key,
				&desc_size,
				&desc_ver);
	}

	// Before we can exit UEFI we need to make sure that
	// the following task has completed	
	if (EFI_ERROR(ret)) {
		boot_services_exited = false;
		printf(L"Failed to grow memory map before exit!\n");
		return ret;
	}

	ret = BS->exit_boot_services(img_handle, map_key);

	// Ensure we actually exited...
	if (EFI_ERROR(ret)) {
		boot_services_exited = false;
		printf(L"Failed to exit boot services! (%r)\n", ret);
		return ret;
	}

	// We're now out of UEFI! No going back!
	boot_services_exited = true;

	// This must be done for runtime services. It makes
	// them switch from their physical address to
	// their virtual address
	ret = RT->set_virtual_address_map(map_size,
			desc_size,
			desc_ver,
			map);

	if (EFI_ERROR(ret)) {
		printf(L"Failed to set virtual address map! (%r)\n", ret);
		return ret;
	}

	// Update memory map details
	m->map_key = map_key;
	m->map_key = map_key;
	m->desc_size = desc_size;
	m->desc_version = desc_ver;

	return EFI_SUCCESS;
}
