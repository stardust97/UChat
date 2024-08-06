# 1. 安装C++环境
```shell
sudo apt-get update 
sudo apt-get install -y build-essential 
sudo apt-get install -y git 
sudo apt-get install -y vim 
sudo apt-get install -y cmake
```

# 2. 安装jsoncpp、spdlog
```shell
sudo apt-get install libjsoncpp-dev 
sudo apt-get install libspdlog-dev 
```

# 3. 安装GoogleTest
```shell
git clone https://github.com/google/googletest.git
cd googletest
cmake .
make
sudo make install
```

boost与grpc的安装需要放在 同一个路径下，如：
boost安装在YourPath/boost，grpc安装在 YourPath/grpc中，
需要设置third_party_path环境变量，否则编译无法通过，
以下YourPath需要替换为实际安装路径
# 4. 安装boost1.82：
  1. 下载boost源码 boost_1_82_0.tar.gz https://archives.boost.io/release/1.82.0/source/
  2. 安装boost
   ```shell
  tar -xzf boost_1_82_0.tar.gz 
  cd boost_1_82_0 
  ./bootstrap.sh --prefix=YourPath 
  ./b2 install && rm -rf boost_1_82_0.tar.gz
  ```

# 5. 安装grpc(包含了protobuf)
```shell
sudo apt-get install autoconf libtool pkg-config
git clone -b v1.28.x https://gitee.com/slrom/grpc
cd grpc
```
替换.gitmodule文件里的内容
```
[submodule "third_party/zlib"]
	path = third_party/zlib
	url = https://gitee.com/slrom/zlib.git
	# When using CMake to build, the zlib submodule ends up with a
	# generated file that makes Git consider the submodule dirty. This
	# state can be ignored for day-to-day development on gRPC.
	ignore = dirty
[submodule "third_party/protobuf"]
	path = third_party/protobuf
	url = https://gitee.com/slrom/protobuf.git
	branch = 3.0.x
[submodule "third_party/gflags"]
	path = third_party/gflags
	url = https://gitee.com/slrom/gflags.git
[submodule "third_party/googletest"]
	path = third_party/googletest
	url = https://gitee.com/slrom/googletest.git
[submodule "third_party/benchmark"]
	path = third_party/benchmark
	url = https://gitee.com/slrom/benchmark.git
[submodule "third_party/boringssl-with-bazel"]
	path = third_party/boringssl-with-bazel
	url = https://gitee.com/slrom/boringssl.git
[submodule "third_party/boringssl"]
	path = third_party/boringssl
	url = https://gitee.com/slrom/boringssl.git
[submodule "third_party/cares/cares"]
	path = third_party/cares/cares
	url = https://gitee.com/slrom/c-ares.git
	branch = cares-1_12_0
[submodule "third_party/bloaty"]
	path = third_party/bloaty
	url = https://gitee.com/slrom/bloaty.git
[submodule "third_party/abseil-cpp"]
	path = third_party/abseil-cpp
	url = https://gitee.com/slrom/abseil-cpp.git
	branch = lts_2020_02_25
[submodule "third_party/envoy-api"]
	path = third_party/envoy-api
	url = https://gitee.com/slrom/data-plane-api.git
[submodule "third_party/googleapis"]
	path = third_party/googleapis
	url = https://gitee.com/slrom/googleapis.git
[submodule "third_party/protoc-gen-validate"]
	path = third_party/protoc-gen-validate
	url = https://gitee.com/slrom/protoc-gen-validate.git
[submodule "third_party/udpa"]
	path = third_party/udpa
	url = https://gitee.com/slrom/udpa.git
[submodule "third_party/libuv"]
	path = third_party/libuv
	url = https://gitee.com/slrom/libuv.git
[submodule "third_party/libcxx"]
    path = third_party/libcxx
	url = https://gitee.com/slrom/libcxx.git
[submodule "third_party/libcxxabi"]
    path = third_party/libcxxabi
	url = https://gitee.com/slrom/libcxxabi.git
```

```shell
git submodule update --init
mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON \
		-DgRPC_BUILD_TESTS=OFF \
		-DCMAKE_INSTALL_PREFIX=YourPath \
		-DBUILD_SHARED_LIBS=ON \
		../..
make -j4
make install  
```
安装完成后，设置third_party_path为YourPath
```shell
vim ~/.bashrc
# 在最后一行加上
export third_party_path=YourPath
#退出编辑后更新环境变量
source ~/.bashrc
```


# 6. 生成.pb文件(如果需要更新)
仓库中默认的{.pb文件想要生成的路径}为GateServer/proto, {message文件所在路径}默认也在GateServer/proto，如果protoc的路径不在环境变量里，按照以下方式生成：
1. 生成.pb.h与.pb.c
{YourPath}/grpc/bin/protoc --cpp_out .pb文件想要生成的路径 -I message文件所在路径 message文件名称 

2. 生成.grpc.pb.h与.grpc.pb.c
{YourPath}/grpc/bin/protoc --grpc_out .pb文件想要生成的路径 -I message文件所在路径 message文件名称 --plugin=protoc-gen-grpc="{YourPath}/grpc/bin/protoc-gen-grpc"
生成提示缺少动态库时需要
```shell
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:{YourPath}/grpc/lib
```

# 7. nodejs安装grpc-js
```shell
npm cache clean --force
npm config set registry https://registry.npmmirror.com
npm install @grpc/grpc-js
npm install @grpc/proto-loader
npm install uuid
npm install nodemailer
npm install fs
```
