CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

include(ExternalProject)

ExternalProject_Add(googletest
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG "release-1.8.0"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(googletest SOURCE_DIR)
ExternalProject_Get_Property(googletest BINARY_DIR)

# Set gtest_include_dirs as a global property that can be accessed anywhere in the cmake build. (More powerful than Parent_scope). We can use parent_scope in this scenario as an alternative
set(GTEST_INCLUDE_DIRS ${SOURCE_DIR}/googletest/include PARENT_SCOPE)
set(GMOCK_INCLUDE_DIRS ${SOURCE_DIR}/googlemock/include PARENT_SCOPE)
set(GTEST_LIBS_DIR ${BINARY_DIR}/googlemock/gtest PARENT_SCOPE)
