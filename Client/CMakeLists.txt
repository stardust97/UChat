cmake_minimum_required(VERSION 3.5.1)
message( "                                                              " )
message( "##############################################################" )
message( "#                                                            #" )
message( "#  Copyright 2018-2023, Hongjing Ltd,  All Rights Reserved.  #" )
message( "#                                                            #" )
message( "#  Calibration is an independent EOL service.                #" )
message( "#  Calibration receive the EOL signal raw data to trigger    #" )
message( "#  offline/online/dynamic calibration.                       #" )
message( "#  If you have any question, Contact                         #" )
message( "#  hyperware@hongjingdrive.com for details.                  #" )
message( "#                                                            #" )
message( "##############################################################" )
message( "                                                              " )

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

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -Wall -g2 -ggdb")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall")
ELSE()
  set(CMAKE_SYSTEM_PLATFORM ubuntu)
  execute_process(COMMAND gcc -dumpfullversion OUTPUT_VARIABLE GCC_VERSION)
  string(REPLACE "\n" "" CMAKE_GCC_VERSION "${GCC_VERSION}")
ENDIF()

project( "UChat_Client" VERSION 2024 LANGUAGES CXX C )
option(SHARED_STATIC "shared static" OFF)
option(INSTALL "install" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(
  ${PROJECT_SOURCE_DIR}/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/lib
)

# ARM Platform
IF(DEFINED COMPILE_TOOLCHAIN_ROOT)
  include_directories(
  )

  link_directories(
  )
# X86 Platform
ELSE()
  include_directories(
  )

  link_directories(
  )
ENDIF()



add_subdirectory(${PROJECT_SOURCE_DIR}/src)

IF(COMPILE_TOOLCHAIN_ROOT_TEST)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test)
ENDIF()


if(INSTALL)
  set(OUTPUT "${PROJECT_SOURCE_DIR}/build/output/client")
  install(TARGETS client_uchat RUNTIME DESTINATION ${OUTPUT}/bin)
  # install({FILES | PROGRAMS} <file>... [...])
endif()

