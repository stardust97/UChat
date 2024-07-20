aux_source_directory(. DIRSRCS)
aux_source_directory(./utils UTILS_DIRSRCS)

#mark why failed in top cmake_lists
# set(env_vars LD_LIBRARY_PATH=/home/tiancheng/3party/install_dir/grpc/lib)
# message("lll : $env{LD_LIBRARY_PATH}")
add_custom_command(
  OUTPUT "${message_proto_srcs}" "${message_proto_hdrs}"  
  # "${message_grpc_srcs}" "${message_grpc_hdrs}"
  COMMAND ${PROTOBUF_PROTOC}
  ARGS  --cpp_out "${message_proto_path}"
  # --grpc_out "${message_proto_path}"
        -I "${message_proto_path}"
        "${message_proto}"
        #  --plugin=protoc-gen-grpc="/home/tiancheng/3party/install_dir/grpc/bin/grpc_cpp_plugin"
  DEPENDS "${message_proto}"
  COMMENT "Generating ${message_proto_srcs} and ${message_proto_hdrs} from ${message_proto}"
  VERBATIM
)
# /home/tiancheng/3party/install_dir/grpc/bin/protoc --grpc_out . -I ./ message.proto --plugin=protoc-gen-grpc="/home/tiancheng/3party/install_dir/grpc/bin/grpc_cpp_plugin"


add_custom_target(protobuf_gen ALL DEPENDS ${message_proto_srcs} ${message_proto_hdrs})  

add_executable(
  gate_server
  ${DIRSRCS} 
  ${UTILS_DIRSRCS}
)

add_dependencies(gate_server protobuf_gen)
target_sources(gate_server PRIVATE   ${message_proto_srcs})
target_link_libraries(
  gate_server
  PRIVATE
  pthread
  spdlog::spdlog
  jsoncpp
  ${Boost_LIBRARIES}
  ${Protobuf_LIBRARIES}
  libprotobuf.so
)