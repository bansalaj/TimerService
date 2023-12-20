# Collect source files
set(SOURCE_FILES
    Timer.cpp
    ThreadPool.cpp
    TimerManager.cpp
)

# create the TimerService library
add_library(TimerService ${SOURCE_FILES})

# Specify the include directories
target_include_directories(TimerService PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../inc)

# Set output directories for the library
set_target_properties(TimerService PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Link against pthread on UNIX-like systems
if(UNIX)
    target_link_libraries(TimerService PUBLIC pthread)
endif()

set_target_properties(TimerService PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)