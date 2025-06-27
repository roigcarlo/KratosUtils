export CC=gcc
export CXX=g++
export BUILD_TYPE="Release"

cmake . -H"." -B"./build"
cmake --build "./build" --target install -- -j8
