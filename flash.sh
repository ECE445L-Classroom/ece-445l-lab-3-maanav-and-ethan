#!/bin/bash

# Get the current directory
Root="$(pwd)"

#remove old build bc reasons
rm -r "${Root}"/build

# Generate build files with CMake
cmake -B build

# Build the project
cmake --build build 

# Flash the binary to the microcontroller
lm4flash "${Root}/build/exe.bin"

#lm4flash "${Root}/cmake-build-debug/exe.bin"

