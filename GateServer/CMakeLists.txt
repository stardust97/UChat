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

find_package(spdlog REQUIRED)
set(third_party_path ~/3party/install_dir)
set(BOOST_INSTALL_DIR "${third_party_path}/boost/lib/cmake/Boost-1.82.0")
set(PROTOBUF_INSALL_DIR "${third_party_path}/grpc/lib/cmake/protobuf")
set(PROTOC_BIN_PATH "${third_party_path}/grpc/bin")

find_package(Boost REQUIRED HINTS ${BOOST_INSTALL_DIR})
MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
MESSAGE( STATUS "Boost_VERSION = ${Boost_VERSION}.")

find_package(Protobuf REQUIRED HINTS ${PROTOBUF_INSALL_DIR} )
MESSAGE( STATUS "Protobuf_version = ${Protobuf_VERSION}.")
MESSAGE( STATUS "Protobuf_INCLUDE_DIRS = ${Protobuf_INCLUDE_DIRS}.")
MESSAGE( STATUS "Protobuf_LIBRARIES = ${Protobuf_LIBRARIES}.")


find_program(PROTOBUF_PROTOC protoc PATHS "${PROTOC_BIN_PATH}" )
if(NOT PROTOBUF_PROTOC)
  message(FATAL_ERROR "protoc not found")
endif()

find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin PATHS "${PROTOC_BIN_PATH}")
if(NOT PROTOBUF_PROTOC)
  message(FATAL_ERROR "grpc_cpp_plugin not found")
endif()

# proto file
get_filename_component(message_proto "${PROJECT_SOURCE_DIR}/proto/message.proto" ABSOLUTE)
# message(STATUS "message_proto: ${message_proto}")
get_filename_component(message_proto_path "${message_proto}" PATH)
# message(STATUS "message_proto_path: ${message_proto_path}")

set(message_proto_srcs ${PROJECT_SOURCE_DIR}/proto/message.pb.cc)
set(message_proto_hdrs ${PROJECT_SOURCE_DIR}/proto/message.pb.h)
# set(message_grpc_srcs ${PROJECT_SOURCE_DIR}/proto/message.grpc.pb.cc)
# set(message_grpc_hdrs ${PROJECT_SOURCE_DIR}/proto/message.grpc.pb.h)
  

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIRS}
  ${Protobuf_INCLUDE_DIRS}
  /home/tiancheng/3party/install_dir/grpc/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/lib
  ${PROTOBUF_LIBRARIES}
  # ${Boost_LIBRARY_DIRS}
  /home/tiancheng/3party/install_dir/grpc/lib
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

IF(COMPILE_TOOLCHAIN_ROOT_TEST)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
ENDIF()

if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/gate_server")
  install(TARGETS gate_server RUNTIME DESTINATION ${OUTPUT}/bin)
  install(FILES ${CMAKE_SOURCE_DIR}/conf/log_setting.json DESTINATION ${OUTPUT}/conf)
endif()