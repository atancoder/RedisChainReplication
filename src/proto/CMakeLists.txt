# Resource: https://cmake.org/cmake/help/v3.9/module/FindProtobuf.html
# https://github.com/ucbrise/cpp_project_template/blob/2551c755464edb3941a73e92e690f6d4a04cae40/src/proto/CMakeLists.txt
cmake_minimum_required(VERSION 2.6)

find_package(Protobuf REQUIRED) # Looks for an installed protobuf package. Finds header and .so file
include_directories(${PROTOBUF_INCLUDE_DIR}) # Handles header files of Protobuf library
include_directories(${CMAKE_CURRENT_BINARY_DIR})
# Make this a global property (easier to use parent scope but this is for practice)
set_property(GLOBAL PROPERTY GENERATED_PROTOBUF_DIRS ${CMAKE_CURRENT_BINARY_DIR}) # Handles header files for our protocol that we defined
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER RepServer_client.proto)
add_library(RepServer_client ${PROTO_SRC})
target_link_libraries(RepServer_client protobuf) # links with libprotobuf.so
