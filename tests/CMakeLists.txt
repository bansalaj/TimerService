cmake_minimum_required(VERSION 3.10)
project(TimerServiceTests)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing with CMake
enable_testing()

# Add the Google Test submodule
add_subdirectory(../googletest googletest)

# Include Google Test and TimerService include directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../inc)

# Add the test executable
add_executable(runUnitTests TimerServiceTests.cpp)

# Set output directory for the test executable
set_target_properties(runUnitTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link against Google Test, TimerService library, and pthread if UNIX
target_link_libraries(runUnitTests gtest gtest_main TimerService)

if (UNIX)
    target_link_libraries(runUnitTests pthread)
endif()

# Add the tests to be run
add_test(NAME TimerServiceTests COMMAND runUnitTests)
