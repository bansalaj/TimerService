#!/bin/bash

# Exit the script if any commands fails
set -e

# Intialize and update the Google Test submodule
echo "Initializing and updating Google Test submodule ...."
git submodule init
git submodule update

echo "Creating build directory..."
mkdir -p build
cd build

echo "Generating Makefiles with CMake..."
cmake ..

echo "Building the project..."
make

echo "Binaries can be found in build/bin"

echo "Setup completed successfully."