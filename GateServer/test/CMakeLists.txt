find_package(GTest REQUIRED)

# add_executable(
#   test_gate_server
#   test_gate_server.cpp
# )

# add_executable(
#   test_http_connection
#   test_http_connection.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/../src/http_connection.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/../src/logic_system.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils/logger.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/../src/verify_grpc_client.cpp
#   ${message_proto_srcs}
#   ${message_grpc_srcs}
# )

add_executable(
  test_get_code
  test_get_code.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/common/server_setting.cpp
  ${message_proto_srcs}
  ${message_grpc_srcs}
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils/logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/rpc/verify_grpc_client.cpp

)


# target_link_libraries(
#   test_gate_server
#   PRIVATE
#   pthread
# )

# target_link_libraries(
#   test_http_connection
#   PRIVATE
#   pthread
#   gtest gtest_main
#   protobuf::libprotobuf
#   gRPC::grpc++
#   spdlog::spdlog
#   jsoncpp
# )

target_link_libraries(
  test_get_code
  PRIVATE
  pthread
  protobuf::libprotobuf
  gRPC::grpc++
  spdlog::spdlog
  jsoncpp
)



if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  # install(TARGETS test_gate_server RUNTIME DESTINATION ${OUTPUT}/test/bin)
  # install(TARGETS test_http_connection RUNTIME DESTINATION ${OUTPUT}/test/bin)
  install(TARGETS test_get_code RUNTIME DESTINATION ${OUTPUT}/test/bin)

endif()

