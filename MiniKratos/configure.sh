#!/bin/sh

rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile
cmake -B./build .

cd build
make clean
make
