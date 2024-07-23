#！/bin/bash

cd build/output/gate_server/test
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${third_party_path}/grpc/lib

./bin/test_http_connection
