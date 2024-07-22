#！/bin/bash

cd build/output/gate_server
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${third_party_path}/grpc/lib

./bin/gate_server

