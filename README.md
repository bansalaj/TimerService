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
3. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
4. Run CMake and build the project:
   ```bash
   cmake ..
   make
   ```

This will compile the TimerService library and place the output in the `build` directory.

## Building and Running the Example

The TimerService library comes with an example application demonstrating its usage.

1. Navigate to the example directory inside the project:
   ```bash
   cd path/to/TimerService/example
   ```
2. Create and navigate to the build directory:
   ```bash
   mkdir build && cd build
   ```
3. Run CMake and make to build the example:
   ```bash
   cmake ..
   make
   ```
4. Run the example application:
   ```bash
   ./timer_example
   ```

The example application will show the TimerService library in action, creating and managing both one-shot and periodic timers.

---
