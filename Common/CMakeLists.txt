cmake_minimum_required(VERSION 3.15.1)


IF(COMPILE_TOOLCHAIN_ROOT_DEBUG)
  message("compile target Debug")
  set(CMAKE_BUILD_TYPE Debug)
ELSE()
  message("compile target Release")
  set(CMAKE_BUILD_TYPE Release)
ENDIF()

IF(DEFINED COMPILE_TOOLCHAIN_ROOT)
  message("compile ARM, target ${COMPILE_TOOLCHAIN_ROOT}")
  set(TOOLCHAIN_COMPILER "gcc-linaro-6.5.0-2018.12-x86_64_aarch64-linux-gnu")
  message(STATUS "Compile ARM, targetfs ${COMPILE_TOOLCHAIN_ROOT}")
  message(STATUS "Compile ARM, toolchain ${TOOLCHAIN_COMPILER}")
  set(TOOLCHAIN_COMPILER_ROOT "${COMPILE_TOOLCHAIN_ROOT}/${TOOLCHAIN_COMPILER}/bin")

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_PROCESSOR arm)
  set(CMAKE_SYSTEM_PLATFORM aarch64)
  set(CMAKE_GCC_VERSION 6.5.0)

  set(CMAKE_CXX_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-linux-gnu-g++)
  set(CMAKE_C_COMPILER ${TOOLCHAIN_COMPILER_ROOT}/aarch64-linux-gnu-gcc)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g2 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
ELSE()
  set(CMAKE_SYSTEM_PLATFORM ubuntu)
  execute_process(COMMAND gcc -dumpfullversion OUTPUT_VARIABLE GCC_VERSION)
  string(REPLACE "\n" "" CMAKE_GCC_VERSION "${GCC_VERSION}")
ENDIF()

set(CMAKE_CXX_STANDARD 17)
project( "Uchat" VERSION 2024 LANGUAGES CXX C )
option(SHARED_STATIC "shared static" OFF)
option(INSTALL "install" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_subdirectory(${PROJECT_SOURCE_DIR}/net)
