export CC=clang
export CXX=clang++
export BUILD_TYPE="Release"

cmake . -H"." -B"./build"
cmake --build "./build" --target install -- -j8
