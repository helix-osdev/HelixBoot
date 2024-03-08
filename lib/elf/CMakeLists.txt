target_sources(${HELIX_TARGET} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_open.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_check.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_load.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_shdrs.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_phdrs.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_close.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_utils.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_sym.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_dyn.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_start.c"
)
