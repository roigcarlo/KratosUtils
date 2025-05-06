#include <vector>
#include <ranges>
#include <numeric>
#include <iostream>
#include <execution>

#include <sycl/sycl.hpp>

#include "utils/perf.h"

int main() {
    static constexpr std::size_t p_size = 1e8;
    static constexpr std::size_t reps = 5;
    
    std::vector v(p_size,0);

    // SYCL queue creation
    // sycl::queue q(sycl::default_selector_v);

    // SYCL queue creation (With profiling info)
    sycl::queue q(sycl::default_selector_v, {sycl::property::queue::enable_profiling()});

    auto dev = q.get_device();
    std::cout << "Device: "                     << dev.get_info<sycl::info::device::name>() << "\n";
    std::cout << "Vendor: "                     << dev.get_info<sycl::info::device::vendor>() << "\n";
    std::cout << "Compute Units: "              << dev.get_info<sycl::info::device::max_compute_units>() << "\n";
    std::cout << "Max Work Group Size: "        << dev.get_info<sycl::info::device::max_work_group_size>() << "\n";
    std::cout << "Local Memory Size: "          << dev.get_info<sycl::info::device::local_mem_size>() << " bytes\n";
    std::cout << "Global Memory Size: "         << dev.get_info<sycl::info::device::global_mem_size>() << " bytes\n";
    std::cout << "Max Allocatable Memory: "     << dev.get_info<sycl::info::device::max_mem_alloc_size>() << " bytes\n";
    std::cout << "Max Work Item Dimensions: "   << dev.get_info<sycl::info::device::max_work_item_dimensions>() << "\n";

    for(int r = 0; r < reps; r++) {
        std::iota(v.begin(), v.end(), 0);
        Perf::execute("1-SER ", [&] {
            for (auto & i : v) {
                i *= 2;
            }
        });

        std::iota(v.begin(), v.end(), 0);
        Perf::execute("2-OMP ", [&] {
            #pragma omp parallel for
            for (std::size_t i = 0; i < p_size; i++) {
                v[i] *= 2;
            }
        });

        std::iota(v.begin(), v.end(), 0);
        Perf::execute("3-STD ", [&] {
            std::for_each(
                std::execution::par, 
                std::begin(v), std::end(v), 
                [](auto & i) {
                    i *= 2;
            });
        });

        std::iota(v.begin(), v.end(), 0);
        Perf::execute("4-SYCL", [&] {
            sycl::buffer<int, 1> buffer_v(v.data(), sycl::range<1>(p_size));
            auto e = q.submit([&](sycl::handler & cgh) {
                auto acc_v = buffer_v.get_access<sycl::access::mode::read_write>(cgh);
                return cgh.parallel_for(sycl::range<1>(p_size), [=](sycl::id<1> i) {
                    acc_v[i] *= 2;
                });
            });

            e.wait();

            // Retrieve profiling info (in nanoseconds)
            uint64_t start = e.get_profiling_info<sycl::info::event_profiling::command_start>();
            uint64_t end   = e.get_profiling_info<sycl::info::event_profiling::command_end>();

            // Add the time and convert to microseconds (sycl reports in nano)
            Perf::add_report("5-KERN", (end-start) / 1000);
        });
    }

    // Check the results
    for (auto & i : v | std::views::take(10)) {
        std::cout << i << " ";
    }

    std::cout << "..." << std::endl;

    return 0;
}