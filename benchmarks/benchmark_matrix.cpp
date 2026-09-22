#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

#include "matrix.hpp"

void run_benchmark(std::size_t size, int repetitions)
{
    Matrix A(size, size);
    Matrix B(size, size);

    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < size; ++j)
        {
            A(i, j) = 1.0f;
            B(i, j) = 2.0f;
        }
    }

    using clock = std::chrono::steady_clock;

    Matrix warmup = A * B;
    volatile float warmup_checksum = warmup(0, 0);

    std::vector<double> times;

    float checksum = 0.0f;

    for (int run = 0; run < repetitions; ++run)
    {
        auto start = clock::now();

        Matrix C = A * B;

        auto end = clock::now();

        checksum += C(0, 0);

        std::chrono::duration<double, std::milli> elapsed =
            end - start;

        times.push_back(elapsed.count());
    }

    double average_ms = std::accumulate(times.begin(), times.end(), 0.0) / times.size();

    double min_ms = *std::min_element(times.begin(), times.end());

    std::sort(times.begin(), times.end());
    double median_ms;

    if (times.size() % 2 == 0)
    {
        median_ms = (times[times.size() / 2] + times[times.size() / 2 - 1]) / 2.0;
    }
    else
    {
        median_ms = times[times.size() / 2];
    }

    double operations =
        2.0 *
        static_cast<double>(size) *
        static_cast<double>(size) *
        static_cast<double>(size);

    double median_seconds = median_ms / 1000.0;

    double gflops = operations / median_seconds / 1e9;

std::cout << size << "x" << size
          << ": average = " << average_ms << " ms"
          << ", median = " << median_ms << " ms"
          << ", min = " << min_ms << " ms"
          << ", GFLOPS = " << gflops
          << ", checksum = " << checksum
          << std::endl;
}

int main()
{
    constexpr int repetitions = 5;

    run_benchmark(64, repetitions);
    run_benchmark(128, repetitions);
    run_benchmark(256, repetitions);
    run_benchmark(512, repetitions);
}

