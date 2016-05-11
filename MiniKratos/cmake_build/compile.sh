#!/bin/sh

rm -rf CMakeFiles cmake_install.cmake CMakeCache.txt Makefile
cmake .

make clean
make
