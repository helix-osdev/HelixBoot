#ifndef EFI_API_H
#define EFI_API_H

#include <stdint.h>
#include <stdbool.h>
#include <efi_def.h>


// Forward declaration workaround for GCC/Clang
typedef struct efi_text_input_proto_t efi_text_input_proto_t;
typedef struct efi_text_output_proto_t efi_text_output_proto_t;
typedef struct efi_configuration_table_t efi_configuration_table_t;
typedef struct efi_memory_descriptor_t efi_memory_descriptor_t;
typedef struct efi_time_t efi_time_t;
typedef struct efi_guid_t efi_guid_t;
typedef struct efi_file_info_t efi_file_info_t;
typedef struct efi_time_capabilities_t efi_time_capabilities_t;
typedef struct efi_loaded_image_proto_t efi_loaded_image_proto_t;
typedef struct efi_system_table_t efi_system_table_t;
typedef struct efi_boot_services_t efi_boot_services_t;
typedef struct efi_runtime_services_t efi_runtime_services_t;
typedef struct efi_device_path_proto_t efi_device_path_proto_t;
typedef struct efi_filesystem_proto_t efi_filesystem_proto_t;
typedef struct efi_file_proto_t efi_file_proto_t;








#define EFI_FILE_MODE_READ   0x0000000000000001
#define EFI_FILE_MODE_WRITE  0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY   0x0000000000000001
#define EFI_FILE_HIDDEN      0x0000000000000002
#define EFI_FILE_SYSTEM      0x0000000000000004
#define EFI_FILE_RESERVED    0x0000000000000008
#define EFI_FILE_DIRECTORY   0x0000000000000010
#define EFI_FILE_ARCHIVE     0x0000000000000020
#define EFI_FILE_VALID_ATTR  0x0000000000000037

typedef efi_status_t
(EFI_API *efi_file_open) (
		IN efi_file_proto_t		*this,
		OUT efi_file_proto_t	**new_handle,
		IN char16_t				*name,
		IN uint64_t				open_mode,
		IN uint64_t				attributes
		);

typedef efi_status_t
(EFI_API *efi_file_close) (
		IN efi_file_proto_t		*this
		);

typedef efi_status_t
(EFI_API *efi_file_delete) (
		IN efi_file_proto_t		*this
		);

typedef efi_status_t
(EFI_API *efi_file_read) (
		IN efi_file_proto_t		*this,
		IN OUT uint64_t			*buffer_size,
		OUT void				*buffer
		);

typedef efi_status_t
(EFI_API *efi_file_write) (
		IN efi_file_proto_t		*this,
		IN OUT uint64_t			buffer_size,
		IN void					*buffer
		);

typedef efi_status_t
(EFI_API *efi_file_set_position) (
		IN efi_file_proto_t		*this,
		IN uint64_t				position
		);

typedef efi_status_t
(EFI_API *efi_file_get_position) (
		IN efi_file_proto_t		*this,
		OUT uint64_t			*position
		);

typedef efi_status_t
(EFI_API *efi_file_get_info) (
		IN efi_file_proto_t		*this,
		IN efi_guid_t			*info_type,
		IN OUT uint64_t			*buffer_size,
		OUT void				*buffer
		);

typedef efi_status_t
(EFI_API *efi_file_set_info) (
		IN efi_file_proto_t		*this,
		IN efi_guid_t			*info_type,
		IN OUT uint64_t			buffer_size,
		OUT void				*buffer
		);

typedef struct efi_file_proto_t {
	uint64_t				revision;
	efi_file_open			open;
	efi_file_close			close;
	efi_file_delete			delete;
	efi_file_read			read;
	efi_file_write			write;
	efi_file_get_position	get_position;
	efi_file_set_position	set_position;
	efi_file_get_info		get_info;
	efi_file_set_info		set_info;
	void					*flush;
	void					*unused1;
	void					*unused2;
	void					*unused3;
	void					*unused4;
} efi_file_proto_t;

typedef efi_status_t
(EFI_API *efi_filesystem_proto_open_volume) (
		IN efi_filesystem_proto_t		*this,
		OUT efi_file_proto_t			**root
		);

typedef struct efi_filesystem_proto_t {
	uint64_t							revision;
	efi_filesystem_proto_open_volume	open_volume;
} efi_filesystem_proto_t;

typedef struct efi_guid_t {
	uint32_t	time_low;
	uint16_t	time_mid;
	uint16_t	time_and_ver;
	uint8_t		clock_seq_high;
	uint8_t		clock_seq_low;
	uint8_t		node[6];
} efi_guid_t;

typedef struct efi_time_t {
	uint16_t	year;
	uint8_t		month;
	uint8_t		day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
	uint8_t		__padding0;
	uint32_t	nano_second;
	uint16_t	time_zone;
	uint8_t		day_light;
	uint8_t		__padding1;
} efi_time_t;

typedef struct {
	uint64_t 	scan_code;
	char16_t 	unicode_char;
} efi_input_key_t;

typedef struct efi_configuration_table_t {
	efi_guid_t		vendor_guid;
	void			*vendor_table;
} efi_configuration_table_t;

typedef struct efi_file_info_t {
	uint64_t		size;
	uint64_t		file_size;
	uint64_t		physical_size;
	efi_time_t		create_time;
	efi_time_t		last_access_time;
	efi_time_t		modified_time;
	uint64_t		attributes;
	char16_t		file_name[1];
} efi_file_info_t;

#define SIZE_OF_EFI_FILE_INFO \
	EFI_FIELD_OFFSET(efi_file_info_t, file_name)

#define EFI_GLOBAL_VARIABLE \
	{0x8BE4DF61, 0x93CA, 0x11d2, \
	{0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C}}

#define EFI_ACPI_20_TABLE_GUID \
	{0x8868e871,0xe4f1,0x11d3, \
	{0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}}

#define ACPI_TABLE_GUID \
	{0xeb9d2d30, 0x2d88, 0x11d3, \
	0x9a, 0x16, {0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}

#define SAL_SYSTEM_TABLE_GUID \
	{0xeb9d2d32,0x2d88,0x11d3, \
	{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS_TABLE_GUID \
	{0xeb9d2d31,0x2d88,0x11d3, \
	{0x9a,0x16,0x00,0x90,0x27,0x3f,0xc1,0x4d}}

#define SMBIOS3_TABLE_GUID \
	{0xf2fd1544, 0x9794, 0x4a2c, \
	{0x99,0x2e,0xe5,0xbb,0xcf,0x20,0xe3,0x94}}



#define EFI_DTB_TABLE_GUID \
	{0xb1b621d5,0xf19c,0x41a5, \
	{0x83,0x0b,0xd9,0x15,0x2c,0x69,0xaa,0xe0}}

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} efi_memory_type_t;

typedef enum efi_memory_type_t {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} efi_allocate_type_t;

#define EFI_MEMORY_UC            0x0000000000000001
#define EFI_MEMORY_WC            0x0000000000000002
#define EFI_MEMORY_WT            0x0000000000000004
#define EFI_MEMORY_WB            0x0000000000000008
#define EFI_MEMORY_UCE           0x0000000000000010

#define EFI_MEMORY_WP            0x0000000000001000
#define EFI_MEMORY_RP            0x0000000000002000
#define EFI_MEMORY_XP            0x0000000000004000
#define EFI_MEMORY_RO            0x0000000000020000

#define EFI_MEMORY_NV            0x0000000000008000
#define EFI_MEMORY_RUNTIME       0x8000000000000000

#define EFI_MEMORY_MORE_RELIABLE 0x0000000000010000
#define EFI_MEMORY_SP            0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO    0x0000000000080000
#define EFI_MEMORY_ISA_VALID     0x4000000000000000
#define EFI_MEMORY_ISA_MASK      0x0FFFF00000000000

typedef efi_status_t
(EFI_API *efi_allocate_pages) (
		IN efi_allocate_type_t	type,
		IN efi_memory_type_t	mem_type,
		IN uint64_t				number_of_pages,
		IN OUT uint64_t			*memory
		);

typedef efi_status_t
(EFI_API *efi_free_pages) (
		IN uint64_t		memory,
		IN uint32_t		pages
		);

typedef efi_status_t
(EFI_API *efi_get_memory_map) (
		IN OUT uint64_t				*memory_map_size,
		OUT efi_memory_descriptor_t	*memory_map,
		OUT uint64_t				*memory_map_key,
		OUT uint64_t				*descriptor_size,
		OUT uint32_t				*descriptor_version
		);

typedef efi_status_t
(EFI_API *efi_allocate_pool) (
		IN efi_memory_type_t	pool_type,
		IN uint64_t				pool_size,
		OUT void				**buffer
		);

typedef efi_status_t
(EFI_API *efi_free_pool) (
		IN void		*buffer
		);

typedef efi_status_t
(EFI_API *efi_get_memory_map) (
		IN OUT uint64_t					*map_size,
		OUT	efi_memory_descriptor_t		*memory_map,
		OUT	uint64_t					*map_key,
		OUT uint64_t					*desc_size,
		OUT uint32_t					*desc_version
		);

typedef struct efi_memory_descriptor_t {
	efi_memory_type_t	type;
	uint32_t			__padding;
	uint64_t			physical_start;
	uint64_t			virtual_start;
	uint64_t			number_of_pages;
	uint64_t			attributes;
} efi_memory_descriptor_t;

typedef struct {
	uint32_t					version;
	uint32_t					number_of_entries;
	uint32_t					descriptor_size;
	uint32_t					flags;
	efi_memory_descriptor_t		entry[1];
} efi_memory_attributes_table_t;

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL 0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL 0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL 0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER 0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER 0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE 0x00000020

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} efi_locate_search_type_t;

typedef efi_status_t
(EFI_API *efi_locate_handle) (
		IN efi_locate_search_type_t	search_type,
		IN efi_guid_t				*protocol OPTIONAL,
		IN void						*search_key OPTIONAL,
		IN OUT uint64_t				buffer_size,
		OUT efi_handle_t			*buffer
		);

typedef efi_status_t
(EFI_API *efi_handle_protocol) (
		IN efi_handle_t		handle,
		IN efi_guid_t		*protocol,
		OUT void			**interface
		);

typedef efi_status_t
(EFI_API *efi_open_protocol) (
		IN efi_handle_t		handle,
		IN efi_guid_t		*protocol,
		OUT void			**interface OPTIONAL,
		IN efi_handle_t		agent_handle,
		IN efi_handle_t		controller_handle,
		IN uint32_t			attributes
		);

typedef efi_status_t
(EFI_API *efi_close_protocol) (
		IN efi_handle_t		handle,
		IN efi_guid_t		*protocol,
		IN efi_handle_t		agent_handle,
		IN efi_handle_t		controller_handle
		);

typedef efi_status_t
(EFI_API *efi_locate_handle_buffer) (
		IN efi_locate_search_type_t	search_type,
		IN efi_guid_t				*protocol,
		IN void						*search_key,
		OUT uint64_t				*number_of_handles,
		OUT efi_handle_t			**buffer
		);

typedef efi_status_t
(EFI_API *efi_locate_protocol) (
		IN efi_guid_t	*protocol,
		IN void			*registration OPTIONAL,
		OUT void		**interface
		);



typedef efi_status_t
(EFI_API *efi_exit) (
		IN efi_handle_t		img_handle,
		IN efi_status_t		exit_status,
		IN uint64_t			exit_data_size,
		IN char16_t			*exit_data OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_exit_boot_services) (
		IN efi_handle_t		img_handle,
		IN uint64_t			map_key
		);

typedef efi_status_t
(EFI_API *efi_set_watchdog_timer) (
		IN uint64_t		timeout,
		IN uint64_t		watchdog_code,
		IN uint64_t		data_size,
		IN char16_t		*watchdog_data OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_stall) (
		IN uint64_t micro_seconds
		);

typedef efi_status_t
(EFI_API *efi_copy_mem) (
		IN void			*destination,
		IN void			*source,
		IN uint64_t		length
		);

typedef efi_status_t
(EFI_API *efi_set_mem) (
		IN void			*buffer,
		IN uint64_t		length,
		IN uint8_t		value
		);

typedef efi_status_t
(EFI_API *efi_calculate_crc32) (
		IN void			*data,
		IN uint64_t		data_size,
		OUT uint32_t	*crc32
		);

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_APPEND_WRITE 0x00000040

typedef efi_status_t
(EFI_API *efi_get_variable) (
		IN char16_t			*variable_name,
		IN efi_guid_t		*vendor_guid,
		OUT uint32_t		*attributes OPTIONAL,
		IN uint64_t			data_size,
		OUT void			*data OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_get_variable_name) (
		IN OUT uint64_t		*variable_size,
		IN OUT char16_t		*variable_name,
		IN OUT efi_guid_t	*vendor_guid
		);

typedef efi_status_t
(EFI_API *efi_set_variable) (
		IN char16_t		*variable_name,
		IN efi_guid_t	*vendor_guid,
		IN uint32_t		attributes,
		IN uint64_t		data_size,
		IN void			*data
		);

typedef efi_status_t
(EFI_API *efi_get_time) (
		OUT efi_time_t				*time,
		OUT efi_time_capabilities_t	*capabilities OPTIONAL 
		);

typedef efi_status_t
(EFI_API *efi_set_time) (
		IN efi_time_t		*time
		);

typedef efi_status_t
(EFI_API *efi_get_wakeup_time) (
		OUT bool		*enabled,
		OUT bool		*pending,
		OUT efi_time_t	*time
		);

typedef efi_status_t
(EFI_API *efi_set_wakeup_time) (
		IN bool			enabled,
		IN efi_time_t	*time OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_set_virtual_address_map) (
		IN uint64_t					map_size,
		IN uint64_t					descriptor_size,
		IN uint32_t					descriptor_version,
		IN efi_memory_descriptor_t	*virtual_map
		);

#define EFI_OPTIONAL_PTR 0x00000001

typedef efi_status_t
(EFI_API *efi_convert_pointer) (
		IN uint64_t		debug_disposition,
		IN void			**address
		);

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} efi_reset_type;

typedef efi_status_t
(EFI_API *efi_reset_system) (
		IN efi_reset_type		reset_type,
		IN efi_status_t			reset_status,
		IN uint64_t				data_size,
		IN void					*reset_data OPTIONAL
		);

typedef efi_status_t
(EFI_API *efi_image_unload) (
		IN efi_handle_t		img_handle
		);

typedef efi_status_t
(EFI_API *efi_text_string) (
		IN efi_text_output_proto_t		*this,
		IN char16_t						*string
		);

typedef efi_status_t
(EFI_API *efi_text_clear_screen) (
		IN efi_text_output_proto_t      *this
		);

typedef efi_status_t
(EFI_API *efi_text_set_attribute) (
		IN efi_text_output_proto_t		*this,
		IN uint32_t						attribute
		);

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
	{0x5B1B31A1, 0x9562, 0x11d2, \
	0x8E, 0x3F, {0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}}

#define EFI_LOADED_IMAGE_PROTOCOL_REVISION 0x1000

#define EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_GUID \
	{0xbc62157e, 0x3e33, 0x4fec, \
	{0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf}}

#define EFI_DEVICE_PATH_PROTOCOL_GUID \
	{0x09576e91, 0x6d3f, 0x11d2, \
	0x8e, 0x39, {0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

#define EFI_FILE_SYSTEM_VOLUME_LABEL_ID \
	{0xdb47d7d3, 0xfe81, 0x11d3, 0x9a35, \
	{0x00, 0x90, 0x27, 0x3f, 0xC1, 0x4d}}

#define MAX_VOLUME_NAME 256

typedef struct {
	char16_t		label[MAX_VOLUME_NAME];
} efi_file_system_volume_label_t;

typedef struct efi_device_path_proto_t {
	uint8_t		type;
	uint8_t		sub_type;
	uint8_t		length[2];
} efi_device_path_proto_t;

typedef struct efi_loaded_image_proto_t {
	uint32_t			revision;
	efi_handle_t		parent_handle;
	efi_system_table_t	*system_table;
	efi_handle_t		device_path;
	void				*file_path;
	void				*reserved;
	uint32_t			load_options_size;
	void				*load_options;
	void				*image_base;
	uint64_t			image_size;
	efi_memory_type_t	image_code_type;
	efi_memory_type_t	image_data_type;
	efi_image_unload	unload;
} efi_loaded_image_proto_t;

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
	{0x387477c1,0x69c7,0x11d2, \
	{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef efi_status_t
(EFI_API *efi_input_reset) (
		IN efi_text_input_proto_t	*this,
		IN bool						extended_verification
		);

typedef efi_status_t
(EFI_API *efi_input_read_key) (
		IN efi_text_input_proto_t	*this,
		IN efi_input_key_t			*key
		);

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
	{0x387477c2,0x69c7,0x11d2, \
	{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef efi_status_t
(EFI_API *efi_text_reset) (
		IN efi_text_output_proto_t	*this,
		IN bool						extended_verification
		);

typedef efi_status_t
(EFI_API *efi_text_test_string) (
		IN efi_text_output_proto_t	*this,
		IN char16_t					*string
		);

typedef efi_status_t
(EFI_API *efi_text_query_mode) (
		IN efi_text_output_proto_t	*this,
		IN uint64_t					mode_number,
		OUT uint64_t				*columns,
		OUT uint64_t				*rows
		);

typedef efi_status_t
(EFI_API *efi_text_set_mode) (
		IN efi_text_output_proto_t	*this,
		IN uint64_t					mode_number
		);

typedef efi_status_t
(EFI_API *efi_text_set_cursor_position) (
		IN efi_text_output_proto_t	*this,
		IN uint64_t					column,
		IN uint64_t					row
		);

typedef efi_status_t
(EFI_API *efi_text_enable_cursor) (
		IN efi_text_input_proto_t	*this,
		IN bool						visible
		);

typedef struct efi_text_input_proto_t {
	efi_input_reset			reset;
	efi_input_read_key		read_key_stroke;
	efi_event_t				wait_for_event;
} efi_text_input_proto_t;

typedef struct efi_text_output_proto_t {
	efi_text_reset			reset;
	efi_text_string			output_string;
	efi_text_test_string	test_string;
	efi_text_query_mode		query_mode;
	efi_text_set_mode		set_mode;
	efi_text_set_attribute	set_attribute;
	efi_text_clear_screen	clear_screen;
	efi_text_set_cursor_position set_cursor_pos;
	efi_text_enable_cursor	enable_cursor;
	void					*mode;
} efi_text_output_proto_t;

#define EFI_TIME_ADJUST_DAYLIGHT 0x01
#define EFI_TIME_IN_DAYLIGHT 0x02
#define EFI_UNSPECIFIED_TIMEZONE 0x07FF

typedef struct efi_time_capabilities_t {
	uint32_t		resolution;
	uint32_t		accuracy;
	bool			sets_to_zero;
} efi_time_capabilities_t;

typedef struct {
	uint64_t	signature;
	uint32_t	revision;
	uint32_t	header_size;
	uint32_t	crc32;
	uint32_t	reserved;
} efi_table_header_t;

typedef struct {
	char		signature[8];
	uint8_t		checksum;
	char		oem_id[6];
	uint8_t		revision;
	uint32_t	rsdp_address;
} efi_rsdp_t;

typedef struct efi_boot_services_t {
	efi_table_header_t		hdr;
	void					*raise_tpl;
	void					*restore_tpl;
	efi_allocate_pages		allocate_pages;
	efi_free_pages			free_pages;
	efi_get_memory_map		get_memory_map;
	efi_allocate_pool		allocate_pool;
	efi_free_pool			free_pool;
	void					*create_event;
	void					*set_timer;
	void					*wait_for_event;
	void					*signal_event;
	void					*close_event;
	void					*check_event;
	void					*install_protocol_interface;
	void					*reinstall_protocol_interface;
	void					*uninstall_protocol_interface;
	efi_handle_protocol		handle_protocol;
	void					*reserved;
	void					*register_protocol_notify;
	efi_locate_handle		locate_handle;
	void					*locate_device_path;
	void					*install_configuration_table;
	void					*load_image;
	void					*start_image;
	efi_exit				exit;
	void					*unload_image;
	efi_exit_boot_services	exit_boot_services;
	void					*get_next_monotonic_count;
	efi_stall				stall;
	efi_set_watchdog_timer	set_watchdog_timer;
	void					*connect_controller;
	void					*disconnect_controller;
	efi_open_protocol		open_protocol;
	efi_close_protocol		close_protocol;
	void					*open_protocol_information;
	void					*protocols_per_handle;
	efi_locate_handle_buffer locate_handle_buffer;
	efi_locate_protocol		locate_protocol;
	void					*install_multiple_proto;
	void					*uninstall_multiple_proto;
	efi_calculate_crc32		calculate_crc32;
	efi_copy_mem			copy_mem;
	efi_set_mem				set_mem;
	void					*create_event_ex;
} efi_boot_services_t;

typedef struct efi_runtime_services_t  {
	efi_table_header_t		hdr;
	efi_get_time			get_time;
	efi_set_time			set_time;
	efi_get_wakeup_time		get_wakeup_time;
	efi_set_wakeup_time		set_wakeup_time;
	efi_set_virtual_address_map set_virtual_address_map;
	efi_convert_pointer		convert_pointer;
	efi_get_variable		get_variable;
	efi_get_variable_name	get_variable_name;
	efi_set_variable		set_variable;
	void					*get_next_high_monotonic_count;
	efi_reset_system		reset_system;
	void					*update_capsule;
	void					*query_capsule_capabilities;
	void					*query_variable_info;
} efi_runtime_services_t;

typedef struct efi_system_table_t {
	efi_table_header_t		hdr;
	char16_t				*firmware_vendor;
	uint32_t				firmware_revision;
	efi_handle_t			con_in_handle;
	efi_text_input_proto_t	*con_in;
	efi_handle_t			con_out_handle;
	efi_text_output_proto_t	*con_out;
	efi_handle_t			stderr_handle;
	efi_text_output_proto_t	*stderror;
	efi_runtime_services_t	*runtime_services;
	efi_boot_services_t 	*boot_services;
	uint32_t				number_of_table_entries;
	efi_configuration_table_t *configuration_table;
} efi_system_table_t;

#endif
