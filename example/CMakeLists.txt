cmake_minimum_required(VERSION 3.10)
project(TimerExample)

# Add the executable for the example
add_executable(timer_example example.cpp)

# Set output directory for the executable
set_target_properties(timer_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link the TimerService library to the example executable
target_link_libraries(timer_example TimerService)