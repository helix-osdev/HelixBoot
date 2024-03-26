cmake_minimum_required(VERSION 3.5)

project(helix_uefi LANGUAGES C ASM)

include(cmake/config.cmake)

set(CMAKE_ASM_COMPILER "/usr/bin/clang")
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_LINKER "/usr/bin/clang")

set(HELIX_ARCH "arm64" CACHE STRING "")

set(HELIX_TARGET "helix_boot.efi")

include(cmake/qemu-ovmf-${HELIX_ARCH}.cmake)


set(OVMF
	"QEMU_EFI_${HELIX_ARCH}.fd" CACHE FILEPATH ""
)

set(OVMF_VARS
	"QEMU_VARS_${HELIX_ARCH}.fd" CACHE FILEPATH ""
)

if (NOT EXISTS "${HELIX_EXT}/${OVMF}")
	message(STATUS "Downloading ${OVMF}")

	file(DOWNLOAD 
		"${QEMU_OVMF}" "${HELIX_EXT}/${OVMF}"
	)
endif()





add_executable(${HELIX_TARGET})

target_include_directories(${HELIX_TARGET} PRIVATE
	"${HELIX_SOURCE_DIR}/include"
)

target_compile_options(${HELIX_TARGET} PRIVATE
	-target aarch64-unknown-windows
	-ffreestanding
	-fshort-wchar
	-mcpu=cortex-a57
	-mgeneral-regs-only
	-Wno-unused-command-line-argument
)

target_link_options(${HELIX_TARGET} PRIVATE
	-target aarch64-unknown-windows
	-nostdlib
	-Wl,-entry:efi_main
	-Wl,-subsystem:efi_application
	-fuse-ld=lld-link
)



add_subdirectory(arch/arm64)
add_subdirectory(init)
add_subdirectory(lib)
add_subdirectory(mm)
add_subdirectory(devices)
add_subdirectory(scripts)
