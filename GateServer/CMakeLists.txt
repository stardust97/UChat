cmake_minimum_required(VERSION 3.15)

IF(COMPILE_TOOLCHAIN_ROOT_DEBUG)
  message("compile target Debug")
  set(CMAKE_BUILD_TYPE Debug)
ELSE()
  message("compile target Release")
  set(CMAKE_BUILD_TYPE Release)
ENDIF()

set(CMAKE_SYSTEM_PLATFORM ubuntu)
execute_process(COMMAND gcc -dumpfullversion OUTPUT_VARIABLE GCC_VERSION)
string(REPLACE "\n" "" CMAKE_GCC_VERSION "${GCC_VERSION}")

set(CMAKE_CXX_STANDARD 17)
project( "UChat_Client" VERSION 2024 LANGUAGES CXX C )
option(SHARED_STATIC "shared static" OFF)
option(INSTALL "install" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



if(NOT DEFINED ENV{third_party_path})
	message(FATAL_ERROR "not defined environment variable:third_party_path")  
endif()
message("third_party_path: $ENV{third_party_path}")
set(third_party_path $ENV{third_party_path})

set(BOOST_CONFIG_DIR "${third_party_path}/boost/lib/cmake/Boost-1.82.0")
set(PROTOBUF_CONFIG_DIR "${third_party_path}/grpc/lib/cmake/protobuf")
set(GRPC_CONFIG_DIR "${third_party_path}/grpc/lib/cmake/grpc")
set(GRPC_INSTALL_DIR  "${third_party_path}/grpc")
set(PROTOC_BIN_PATH "${third_party_path}/grpc/bin")
set(Protobuf_DIR "${third_party_path}/grpc/lib/cmake/protobuf")

find_package(spdlog REQUIRED)
add_compile_definitions(SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
find_package(Boost REQUIRED HINTS ${BOOST_CONFIG_DIR})
find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC REQUIRED HINTS ${GRPC_CONFIG_DIR})


# find_program(PROTOBUF_PROTOC protoc PATHS "${PROTOC_BIN_PATH}" )
# if(NOT PROTOBUF_PROTOC)
#   message(FATAL_ERROR "protoc not found")
# endif()

# find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin PATHS "${PROTOC_BIN_PATH}")
# if(NOT PROTOBUF_PROTOC)
#   message(FATAL_ERROR "grpc_cpp_plugin not found")
# endif()

# proto file
get_filename_component(message_proto "${PROJECT_SOURCE_DIR}/proto/message.proto" ABSOLUTE)
# message(STATUS "message_proto: ${message_proto}")
get_filename_component(message_proto_path "${message_proto}" PATH)
# message(STATUS "message_proto_path: ${message_proto_path}")

set(message_proto_srcs ${PROJECT_SOURCE_DIR}/proto/message.pb.cc)
set(message_proto_hdrs ${PROJECT_SOURCE_DIR}/proto/message.pb.h)
set(message_grpc_srcs ${PROJECT_SOURCE_DIR}/proto/message.grpc.pb.cc)
set(message_grpc_hdrs ${PROJECT_SOURCE_DIR}/proto/message.grpc.pb.h)


include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
  ${message_proto_path}
)

link_directories(
  ${PROJECT_SOURCE_DIR}/lib
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

IF(COMPILE_TOOLCHAIN_ROOT_TEST)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
ENDIF()

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  install(TARGETS gate_server RUNTIME DESTINATION ${OUTPUT}/bin)
  file(GLOB JSON_FILES "${CMAKE_SOURCE_DIR}/conf/*.json")  
  install(FILES ${JSON_FILES} DESTINATION ${OUTPUT}/conf)
endif()