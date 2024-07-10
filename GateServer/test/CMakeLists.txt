add_executable(
  test_gate_server
  test_gate_server.cpp
)

add_executable(
  test_http_connection
  test_http_connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/http_connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/logic_system.cpp

)

target_link_libraries(
  test_gate_server
  PRIVATE
  pthread
)

target_link_libraries(
  test_http_connection
  PRIVATE
  pthread
)


if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  install(TARGETS test_gate_server RUNTIME DESTINATION ${OUTPUT}/test/bin)
  install(TARGETS test_http_connection RUNTIME DESTINATION ${OUTPUT}/test/bin)
endif()

