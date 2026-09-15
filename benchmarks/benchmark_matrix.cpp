#include <chrono>
#include <iostream>

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

    double total_ms = 0.0;

    float checksum = 0.0f;

    for (int run = 0; run < repetitions; ++run)
    {
        auto start = clock::now();

        Matrix C = A * B;

        auto end = clock::now();

        checksum += C(0, 0);

        std::chrono::duration<double, std::milli> elapsed =
            end - start;

        total_ms += elapsed.count();
    }

    double average_ms = total_ms / repetitions;

    std::cout << size << "x" << size
            << ": "
            << average_ms
            << " ms average"
            << ", checksum = "
            << checksum
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

