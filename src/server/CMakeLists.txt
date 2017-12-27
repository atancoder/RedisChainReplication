cmake_minimum_required (VERSION 3.0)

project(replicated_server)

#include_directories(${CPP_REDIS_INCLUDE_DIRS})
#link_directories(${CPP_REDIS_LINK_DIRS})

add_executable(replicated_server replicated_server.cpp)
add_dependencies(replicated_server redis_client) #Ensure that redis_client target is built first (target names are global throughout the build tree)

# Very important that we link only after we specify the app creation (add_executable)
# target_link_libraries creates the -l flag in the g++ compiler (in our case, -lcpp_redis)
target_link_libraries(replicated_server
    cpp_redis
)

