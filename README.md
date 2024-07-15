# 1. 安装C++环境
  ```shell
    apt-get update 
    apt-get install -y build-essential 
    apt-get install -y git 
    apt-get install -y vim 
    apt-get install -y cmake
  ```

# 2. 安装boost1.82：
  1. 下载boost源码 boost_1_82_0.tar.gz
  2. 安装boost
   ```shell
  tar -xzf boost_1_82_0.tar.gz 
  cd boost_1_82_0 
  ./bootstrap.sh --prefix=YourPath 
  ./b2 install && rm -rf boost_1_82_0.tar.gz
  ```

# 3. 安装jsoncpp、spdlog
```shell
    apt-get update libjsoncpp-dev 
    apt-get update libspdlog-dev 
```

# 4. 安装GoogleTest
```shell
  git clone https://github.com/google/googletest.git
  cd googletest
  cmake .
  make
  make install
```