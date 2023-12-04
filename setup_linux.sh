#!/bin/bash

# Exit the script if any commands fails
set -e

# Intialize and update the Google Test submodule
echo "Initializing and updating Google Test submodule ...."
git submodule init
git submodule update

# create a build directory and navigate into it
echo "Creating build directory..."
mkdir -p build
cd build

# Run CMake and build the project
cmake ..
make

# Navigate back the root dir
cd ..

echo "Setup completed successfully."