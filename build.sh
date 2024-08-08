#!/bin/bash

# This script builds the SimpleMultiThreadedOS using the i686-elf cross compiler

# Set the prefix for the cross compiler tools
export PREFIX="$HOME/opt/cross"

# Set the target architecture for the cross compiler
export TARGET=i686-elf

# Add the cross compiler bin directory to the PATH
export PATH="$PREFIX/bin:$PATH"

#create a folder idt and memory inside build directory
cd build
mkdir -p idt
mkdir -p memory
cd ..

# Run the make command to build the project
make all
