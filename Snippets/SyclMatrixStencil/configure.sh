# Load intel libraries
source /home/roigcarlo/intel/oneapi/2024.0/oneapi-vars.sh intel64

export CXX=icpx
export BUILD_TYPE="Release"

# Configure
cmake -H"src" -B"build/${BUILD_TYPE}" -G Ninja -DCMAKE_INSTALL_PREFIX="./bin" \
-DCMAKE_CXX_FLAGS="-fsycl -fsycl-targets=nvptx64-nvidia-cuda -fsycl-unnamed-lambda"

# Build core
cmake --build "build/${BUILD_TYPE}" --target install -- -j$(nproc)
