---

# TimerService Library

## Introduction

TimerService is a C++ library designed to provide an easy-to-use interface for scheduling and managing timers. It allows users to create one-shot or periodic timers and attach callbacks that are executed when the timers expire. The library is designed to be cross-platform, working on both UNIX-like systems and Windows.

## Features

- **One-Shot Timers**: Create a timer that fires once after a specified duration.
- **Periodic Timers**: Create a timer that repeatedly fires at regular intervals.
- **Callback Functionality**: Attach a function or a lambda expression to be executed when the timer expires.
- **Thread-Safe**: Designed to be safe for use in a multi-threaded environment.
- **Cross-Platform**: Compatible with both UNIX-like systems and Windows.

## Building the Library

To build the TimerService library, you will need CMake and a C++ compiler.

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/TimerService.git
   ```
2. Navigate to the project directory:
   ```bash
   cd TimerService
   ```
4. Update Submodule (GoogleTest)
   ```bash
   git submodule init
   git submodule update
   ```
4. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
5. Run CMake and build the project:
   ```bash
   cmake ..
   make
   ```

This will compile the TimerService library, example and test binaries and place the output in the `build\bin` directory.


The example application will show the TimerService library in action, creating and managing both one-shot and periodic timers.

---
