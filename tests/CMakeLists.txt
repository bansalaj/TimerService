cmake_minimum_required(VERSION 3.10)

project(TimerServiceTests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# enable testing with cmake
enable_testing()

# Add the Google Test submodule
add_subdirectory(../googletest googletest)

# Include Google Test and TimerService include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../inc)

# Add the source files of the library
file(GLOB LIB_SOURCES "../src/*.cpp")

# Add the test executable
add_executable(runUnitTests TimerServiceTests.cpp ${LIB_SOURCES})

# Link against Google Test and the pthread library
if (UNIX)
    target_link_libraries(runUnitTests gtest gtest_main pthread)
endif()

# Add the tests to be run
add_test(NAME TimerServiceTests COMMAND runUnitTests)