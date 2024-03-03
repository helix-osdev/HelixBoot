target_sources(${HELIX_TARGET} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_open.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_check.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_load.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_shdrs.c"
)
