aux_source_directory(. DIRSRCS)

add_executable(
  gate_server
  ${DIRSRCS} 
)

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  install(TARGETS gate_server RUNTIME DESTINATION ${OUTPUT}/bin)
  # install({FILES | PROGRAMS} <file>... [...])
endif()
