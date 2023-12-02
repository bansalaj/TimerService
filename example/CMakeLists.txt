cmake_minimum_required(VERSION 3.10)

project(TimerExample)

# Add the Timerservice Library
add_subdirectory(../src TimerService)

# Add the executable for the example
add_executable(timer_example example.cpp)


# Link the TimerService library to the example exe
target_link_libraries(timer_example TimerService)