FROM ubuntu:20.04

LABEL maintainer="tianchenggg@foxmail.com"

ENV DEBIAN_FRONTEND=noninteractive

#todo protobuf grpc
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    vim \
    wget \
    cmake \
    python3 \
    python3-pip \
    libjsoncpp-dev \
    libspdlog-dev \
    autoconf libtool pkg-config \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /home/uchat_dev

# 安装 Boost 版本
RUN mkdir third_party && cd third_party && mkdir boost

COPY boost /home/uchat_dev/third_party/boost

RUN cd third_party/boost && tar -xzf boost_1_82_0.tar.gz && \
cd boost_1_82_0 && \
./bootstrap.sh --prefix=/home/uchat_dev/third_party/boost && \
./b2 install && rm -rf boost_1_82_0.tar.gz

#安装 jsoncpp到usr/local, /usr/local/include /usr/local/lib
COPY jsoncpp /home/uchat_dev/third_party
RUN cd third_party/jsoncpp && mkdir build && cd build && cmake .. && make && make install


