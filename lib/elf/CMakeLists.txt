target_sources(${HELIX_TARGET} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_load.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_open.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_close.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_verify.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_phdrs.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/elf_shdrs.c"
)
