FROM ubuntu:12.04

RUN apt-get update && apt-get install -y git wget build-essential vim autoconf automake libtool curl make g++ unzip clang

RUN wget 'https://cmake.org/files/v3.6/cmake-3.6.2-Linux-x86_64.sh'
RUN yes | sh cmake-3.6.2-Linux-x86_64.sh
ENV PATH="${PATH}:/cmake-3.6.2-Linux-x86_64/bin"
RUN git clone https://github.com/DevelopingCoder/RedisChainReplication.git
WORKDIR RedisChainReplication

RUN ./build_debug.sh

