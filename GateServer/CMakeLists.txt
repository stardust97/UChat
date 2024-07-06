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

set(boost_path ${PROJECT_SOURCE_DIR}/../../third_party/boost)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${boost_path}/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/lib
  ${boost_path}/lib
)


add_subdirectory(${PROJECT_SOURCE_DIR}/src)

IF(COMPILE_TOOLCHAIN_ROOT_TEST)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
ENDIF()




