#pragma once

#include <chrono>
#include <unordered_map>

namespace Perf {

    class PerfReport {
        public:
            using ChronoReport = std::pair<int, std::chrono::high_resolution_clock::duration>;

            PerfReport() = default;
            ~PerfReport() {
                std::cout << "Name\tTimes\tTotal\t\tAverage" << std::endl;
                for ( const auto & keyval: data) {
                    std::cout << std::scientific << std::setprecision(2);
                    std::cout << keyval.first.substr(0, 10)
                      << "\t" << keyval.second.first 
                      << "\t" << static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(keyval.second.second).count())
                      << "\t" << static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(keyval.second.second).count() / keyval.second.first) << std::endl;
                }
            }

            std::unordered_map<std::string, ChronoReport> data; 
    };

    static PerfReport report;

    void add_report(const std::string & name, double time) {
        auto result = Perf::report.data.insert(std::pair<std::string, Perf::PerfReport::ChronoReport>(
            name, Perf::PerfReport::ChronoReport(0, std::chrono::high_resolution_clock::duration::zero())
        ));
        auto& perf_time = result.first->second;

        perf_time.first++;
        perf_time.second += std::chrono::microseconds(static_cast<long long>(time));
    }

    template <class F> 
    void execute(const std::string & name, const F& f) {
        using namespace std::chrono;

        auto chron_beg = high_resolution_clock::now();
        
        f();

        auto chron_end = high_resolution_clock::now();

        auto result = Perf::report.data.insert(std::pair<std::string, Perf::PerfReport::ChronoReport>(
            name, Perf::PerfReport::ChronoReport(0, std::chrono::high_resolution_clock::duration::zero())
        ));
        auto& perf_time = result.first->second;

        perf_time.first++;
        perf_time.second += (chron_end - chron_beg);
    }
}