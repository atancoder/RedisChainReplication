cmake_minimum_required (VERSION 3.0)

project(redis_chain_replication)

set(CMAKE_CXX_FLAGS_COMMON "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} \
    ${CMAKE_CXX_FLAGS_COMMON}"
    )

# Libraries
add_subdirectory(lib/redis_client) # Runs cmake on this subdirectory to create the Makefile. When you run make, it will also build the subdirectory
add_subdirectory(lib/googletest)

# Link Library Directory
# Similar to -L in g++ compiler. We use this if we didn't create a target_library (ie we didn't create a library for the .a file) and want to link in the application's CMakeLists.txt file
link_directories(${GTEST_LIBS_DIR})

# Include
# Tells the compiler where to look for header files
include_directories(${CPP_REDIS_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

# Testing
enable_testing() #Enable testing so that we can run `make test`. Important that this command is placed before adding the test subdirectory

# Application
add_subdirectory(src)

