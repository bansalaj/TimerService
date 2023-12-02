# Collect source files
set(SOURCE_FILES
    Timer.cpp
    TimerManager.cpp
)

# create the TimerService library
add_library(TimerService ${SOURCE_FILES})

# Specify the include directories
target_include_directories(TimerService PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

# Link against pthread on UNIX-like systems
if(UNIX)
    target_link_libraries(TimerService PUBLIC pthread)
endif()

set_target_properties(TimerService PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)