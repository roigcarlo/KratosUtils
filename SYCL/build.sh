source $HOME/intel/oneapi/setvars.sh intel64 --force

export CC=icp
export CXX=icpx

cmake . -H"." -B"./build"
cmake --build "./build" --target install -- -j8