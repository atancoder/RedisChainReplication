cmake_minimum_required (VERSION 3.0)

project(redis_chain_replication)

set(CMAKE_CXX_FLAGS_COMMON "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} \
    ${CMAKE_CXX_FLAGS_COMMON}")

add_subdirectory(lib/redis_client) # Runs cmake on this subdirectory to create the Makefile. When you run make, it will also build the subdirectory
add_subdirectory(src/server)
