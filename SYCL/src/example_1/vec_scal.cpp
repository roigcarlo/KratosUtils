#include <vector>
#include <ranges>
#include <numeric>
#include <iostream>
#include <execution>

#include "utils/perf.h"

int main() {
    static constexpr std::size_t p_size = 1e8;
    static constexpr std::size_t reps = 5;
    
    std::vector v(p_size,0);

    for(int r = 0; r < reps; r++) {
        std::iota(v.begin(), v.end(), 0);
        Perf::execute("1-SER", [&] {
            for (auto & i : v) {
                i *= 2;
            }
        });

        std::iota(v.begin(), v.end(), 0);
        Perf::execute("2-OMP", [&] {
            #pragma omp parallel for
            for (std::size_t i = 0; i < p_size; i++) {
                v[i] *= 2;
            }
        });

        std::iota(v.begin(), v.end(), 0);
        Perf::execute("3-STD", [&] {
            std::for_each(
                std::execution::par, 
                std::begin(v), std::end(v), 
                [](auto & i) {
                    i *= 2;
            });
        });
    }

    // Check the results
    for (auto & i : v | std::views::take(10)) {
        std::cout << i << " ";
    }

    std::cout << "..." << std::endl;
}