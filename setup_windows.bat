@echo off

echo Cloning Google Test submodule...
git submodule init
git submodule update

echo Creating build directory...
if not exist build mkdir build
cd build

echo Generating project files with CMake...
cmake ..

echo Building the project...
cmake --build .

echo Binaries can be found in build\bin

echo Setup completed successfully.
pause
