cmake_minimum_required(VERSION 3.10)
project(TimerServiceSolution)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the main library source
add_subdirectory(src)

# Include the example application
add_subdirectory(example)

# Include the tests
add_subdirectory(tests)
