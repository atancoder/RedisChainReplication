CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

include(ExternalProject)

# ExternalProject_Add allows us to add external libraries. We supply CMAKE_ARGS  since the project already has a CMakeLists.txt file. 
# On Make: This command will download the repo then run cmake and then make
# Automatically adds inits and updates the tacopie submodule
ExternalProject_Add(redis_client
    GIT_REPOSITORY "https://github.com/Cylix/cpp_redis"
    CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_BUILD_TYPE=Release 
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    INSTALL_COMMAND "" # remove install step
    UPDATE_COMMAND "" # remove update step
    TEST_COMMAND "" # remove test step
    )

# Loads the target's source[binary] directory into SOURCE[BINARY]_DIR
ExternalProject_Get_Property(redis_client SOURCE_DIR)
ExternalProject_Get_Property(redis_client BINARY_DIR)

# We want to establish the location of the library files
set(CPP_REDIS_LIBRARY ${BINARY_DIR}/lib/libcpp_redis.a)
find_library(TACOPIE_LIBRARY tacopie)
if (NOT TACOPIE_LIBRARY)
    # Must make sure tacopie isn't already in the path of the computer. Otherwise this fails because cpp_redis won't create the libtacopie.a
    set(TACOPIE_LIBRARY ${BINARY_DIR}/lib/libtacopie.a)
endif()

# We set this variable so that we can add it to the include_directories
# We add the tacopie includes by adding a semicolon separator
set(CPP_REDIS_INCLUDE_DIRS "${SOURCE_DIR}/includes; ${SOURCE_DIR}/tacopie/includes" PARENT_SCOPE)

# Make cpp_redis a target library that can be referred to in other files
# We use imported and set the location later because the .a file doesn't exist until after we build
add_library(cpp_redis STATIC IMPORTED GLOBAL) #GLOBAL allows us to refer to it in other directories

#Sets the imported_location property to be the libcpp_redis.a file. This is a required property, since this library must be associated with a file, which is provided with the IMPORTED_LOCATION property
set_target_properties(cpp_redis # The target library
    PROPERTIES
    IMPORTED_LOCATION ${CPP_REDIS_LIBRARY}
    INTERFACE_LINK_LIBRARIES "${TACOPIE_LIBRARY};pthread" #This property contains a list of dependent libraries needed to be linked with the target library. So if you link cpp_redis, you are also linking tacopie and pthread
    )

