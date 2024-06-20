aux_source_directory(. DIR_SRCS)

#todo target
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(
  client_uchat
  ${DIR_SRCS}
)
