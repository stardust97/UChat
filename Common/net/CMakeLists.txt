set(boost_path ${PROJECT_SOURCE_DIR}/../../third_party/boost)

file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp")

add_library(net ${SRC_LIST})

target_include_directories(
  net 
  PUBLIC 
  ${boost_path}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/interface
  ${PROJECT_SOURCE_DIR}/impl
)

target_link_directories(
  net 
  PUBLIC 
  ${boost_path}/lib
  pthread
)

