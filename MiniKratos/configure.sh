#!/bin/sh

rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile
cmake -B./build $HOME/KratosUtils/MiniKratos

cd build
make clean
make
