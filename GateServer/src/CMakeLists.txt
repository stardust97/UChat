aux_source_directory(. DIRSRCS)
aux_source_directory(utils UTILS_DIRSRCS)

find_package(spdlog REQUIRED)

add_executable(
  gate_server
  ${DIRSRCS} 
  ${UTILS_DIRSRCS}
)

target_link_libraries(
  gate_server
  PRIVATE
  pthread
  spdlog::spdlog
  jsoncpp
)

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  install(TARGETS gate_server RUNTIME DESTINATION ${OUTPUT}/bin)
  install(FILES ${CMAKE_SOURCE_DIR}/conf/log_setting.json DESTINATION ${OUTPUT}/conf)
endif()
