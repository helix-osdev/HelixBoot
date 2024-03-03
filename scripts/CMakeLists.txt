add_custom_target(setup
	COMMAND
	${CMAKE_COMMAND} -E env "${HELIX_SCRIPTS}/sync.sh" "${HELIX_EXT}" "${HELIX_BINARY_DIR}"
	USES_TERMINAL
)

add_custom_target(run
	COMMAND
	${CMAKE_COMMAND} -E env "${HELIX_SCRIPTS}/boot.sh" "${HELIX_BINARY_DIR}"
	USES_TERMINAL
)

add_custom_target(setup-and-run
	COMMAND ${CMAKE_MAKE_PROGRAM} setup
	COMMAND ${CMAKE_MAKE_PROGRAM} run
	USES_TERMINAL
)
