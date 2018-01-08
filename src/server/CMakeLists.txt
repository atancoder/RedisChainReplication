cmake_minimum_required (VERSION 3.0)

# Make this a library (not global) so that we can use it for testing
add_library(server server.cpp)
add_library(replicated_server replicated_server.cpp)
target_link_libraries(replicated_server cpp_redis RepServer_client server)

# Main is the executable that actually runs the server
add_executable(main main.cpp)

# Very important that we link only after we specify the app creation (add_executable)
# target_link_libraries creates the -l flag in the g++ compiler (in our case, -lreplicated_server)
target_link_libraries(main
    replicated_server
    )

# Testing
add_executable(test_replicated_server test_replicated_server.cpp)
target_link_libraries(test_replicated_server
    replicated_server
    gtest
    gtest_main
    gmock
    gmock_main
    )
add_test(test_replicated_server test_replicated_server)
