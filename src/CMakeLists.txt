cmake_minimum_required (VERSION 3.0)

set(PYTHONPATH ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE) # PARENT_SCOPE so that the variable can be accessed in a different directory
add_subdirectory(server)
add_subdirectory(client)
