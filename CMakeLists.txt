cmake_minimum_required(VERSION 3.10)
project(TimerService)

# Specify the c++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(inc)

# Add the source directory
add_subdirectory(src)