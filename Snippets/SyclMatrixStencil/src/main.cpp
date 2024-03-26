// System includes
#include <chrono>
#include <iostream>

// Intel sycl
#include <CL/sycl.hpp>

void getSyclInfo() {
    queue.submit([&](cl::sycl::handler & cgh) {
        std::cout << "Running on " << queue.get_device().get_info<sycl::info::device::name>() << "\n";
    });
}

template <typename NodeContainerType>
double getNodeAvg(std::size_t i, std::size_t j, std::size_t N, NodeContainerType & nodes) {
    return 0.25 * (
        nodes[(N+1) * (j  ) + i] +
        nodes[(N+1) * (j  ) + i + 1] +
        nodes[(N+1) * (j+1) + i] +
        nodes[(N+1) * (j+1) + i + 1]
    );
}

template <typename NodeContainerType>
void getApplyNodalValue(std::size_t i, std::size_t j, std::size_t N, NodeContainerType & nodes, double value) {
    nodes[(N+1) * (j  ) + i]     += value;
    nodes[(N+1) * (j  ) + i + 1] += value;
    nodes[(N+1) * (j+1) + i]     += value;
    nodes[(N+1) * (j+1) + i + 1] += value;
}

// Executes a function and prints the time it took to execute
template <typename T>
void executeWithTimer(T && func, std::string name, std::size_t times=1000) {
    auto beg = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < times; i++) {
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << name << " took " << std::chrono::duration_cast<std::chrono::microseconds> (end - beg).count() / times << " us/iter" << std::endl;
}

int main() {
    std::cout << "Matrix Stencil Test." << std::endl;

    // Number of elements of the matrix
    constexpr size_t N = 2500;

    // Create a matrix with N*N Elements for CPU and GPU.
    std::vector<double> elems_cpu(N*N, 0.0);
    std::vector<double> elems_gpu(N*N, 0.0);

    // Create a vector with (N+1)*(N+1) Nodes. Its values are its id's
    std::vector<double> nodes((N+1)*(N+1), 0.0);
    std::vector<double> nodes_wrt((N+1)*(N+1), 0.0);

    // Fill the nodes vector
    for (std::size_t i = 0; i < (N+1) * (N+1); i++) {
        nodes[i] = static_cast<double>(i);
    }

    // Setup some parameters
    std::size_t repeat = 10; // 10000; //Should be high in order to remove wind-up effects

    // Fill the matrix with the average of its nodes in CPU
    executeWithTimer([&]() {
        for (std::size_t i = 0; i < N; i++) {
            for (std::size_t j = 0; j < N; j++) {
                elems_cpu[i*N+j] = getNodeAvg(i, j, N, nodes);
            }
        }
    }, "CPU", repeat);

    // They recommend to run on an isolated scope to avoid problems
    {
        // Print sycl queue info
        getSyclInfo();

        // Fill the matrix with the average of its nodes in GPU using SYCL and Global memory only
        cl::sycl::queue queue(sycl::gpu_selector_v);

        // Define the buffers 
        auto elems_gpu_buff = sycl::buffer{elems_gpu.data(), cl::sycl::range<2>{N, N}};
        auto nodes_gpu_buff = sycl::buffer{nodes.data(),     cl::sycl::range<1>{(N+1)*(N+1)}};
        auto nodes_wrt_buff = sycl::buffer{nodes_wrt.data(), cl::sycl::range<1>{(N+1)*(N+1)}};

        executeWithTimer([&]() {
            // Submit the job
            queue.submit([&](cl::sycl::handler & cgh) {
                // Get the accessors from Host buffers to Device buffers
                cl::sycl::accessor elems_gpu_acc{elems_gpu_buff, cgh, sycl::read_write};
                cl::sycl::accessor nodes_gpu_acc{nodes_gpu_buff, cgh, sycl::read_only};
                cl::sycl::accessor nodes_wrt_acc{nodes_wrt_buff, cgh, sycl::read_write};

                // Parallel kernel
                cgh.parallel_for(cl::sycl::range<2>(N,N), [=](cl::sycl::item<2> item) {
                    auto i = item.get_id(0);
                    auto j = item.get_id(1);

                    elems_gpu_acc[i][j] = getNodeAvg(i, j, N, nodes_gpu_acc);

                    getApplyNodalValue(i, j, N, nodes_wrt_acc, elems_gpu_acc[i][j]);
                });
            });

            queue.wait_and_throw();
        }, "GPU", repeat);

        // Get the accessors from Device buffers to Host buffers
        cl::sycl::host_accessor elems_cpu_acc(elems_gpu_buff);

        // Check the results
        for (std::size_t i = 0; i < N; i++) {
            for (std::size_t j = 0; j < N; j++) {
                if (elems_cpu[i*N+j] != elems_cpu_acc[i][j]) {
                    std::cout << "Error at (" << i << ", " << j << "): " << elems_cpu[i*N+j] << " != " << elems_cpu_acc[i][j] << std::endl;
                }
            }
        }
    }
}