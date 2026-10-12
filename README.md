
# C++ Matrix Engine

A matrix computation engine built from scratch in C++17 to explore high-performance computing, CPU optimization, and techniques relevant to AI inference acceleration.

This project focuses on understanding how memory layout, cache locality, SIMD vectorization, and multithreading affect General Matrix Multiplication (GEMM) performance.

## Features

- Row-major matrix storage using `std::vector<float>`
- Bounds-checked element access
- Matrix addition, subtraction, and scalar multiplication
- Matrix transpose
- General matrix multiplication for compatible dimensions
- Cache-aware blocked GEMM (tile size: 128)
- Pointer-based, compiler-friendly inner loops
- SIMD auto-vectorization with AVX2 enabled on MSVC
- OpenMP parallelization across independent output row blocks
- GoogleTest correctness tests
- Benchmarking with warm-up, repeated measurements, median runtime, and GFLOPS

## Optimization Journey

The GEMM implementation was improved incrementally:

1. **Naive GEMM** — Established a baseline implementation.
2. **Memory Access Optimization** — Reordered loops and reduced element-access overhead.
3. **Cache Blocking** — Used tiling to improve data reuse.
4. **Auto-Vectorization** — Simplified the inner loop to enable more effective SIMD code generation.
5. **AVX2** — Enabled 256-bit vector instructions through the compiler.
6. **OpenMP** — Parallelized independent output row blocks across CPU threads.

The optimized GEMM retains the `ii → kk → jj → i → k → j` loop structure, combining cache blocking, SIMD-friendly contiguous accesses, and thread-level parallelism.

### OpenMP Design

```cpp
#pragma omp parallel for schedule(static)
for (std::int64_t block = 0;
     block < static_cast<std::int64_t>(num_i_blocks);
     ++block)
{
    const std::size_t ii =
        static_cast<std::size_t>(block) * BLOCK_SIZE;

    // Each thread processes independent output rows.
    // Remaining loops: kk -> jj -> i -> k -> j
}
```

Each thread owns a distinct range of output rows. Input matrices are read without modification, while the reduction over `k` remains within the thread responsible for each output row block.

## Performance Results

### OpenMP Scaling

Measured on Windows with MSVC Release configuration, AVX2 enabled, and `OMP_DYNAMIC=FALSE`.

Each measurement includes one warm-up and nine timed repetitions. Median runtime is used for comparison.

| OpenMP Threads | 512×512 Median | 1024×1024 Median |
|---|---:|---:|
| 1 | 11.8144 ms | 111.3190 ms |
| 2 | 6.0195 ms | 56.9913 ms |
| 4 (run 1) | 3.8860 ms | 41.8991 ms |
| 4 (run 2) | 3.4056 ms | 37.0087 ms |

Observed speedup relative to the single-thread result:

- **512×512:** 1.96× with 2 threads; 3.04×–3.47× with 4 threads.
- **1024×1024:** 1.95× with 2 threads; 2.66×–3.01× with 4 threads.

Thread-count measurements were interleaved in the order 4 → 1 → 2 → 4 to help assess measurement variability.

These are representative measurements, not guaranteed performance across systems or matrix sizes.

**Measurement scope:** Timing includes the complete matrix multiplication function call, including output matrix allocation.

### Performance Considerations

- Small matrices may not provide enough row blocks to utilize multiple threads effectively.
- Thread creation and scheduling overhead can outweigh the benefits for small workloads.
- Larger workloads can be limited by cache behavior, memory bandwidth, and CPU frequency.
- SIMD vector width and thread count do not directly determine application speedup.

## Build Instructions

### Requirements

- C++17-compatible compiler
- CMake 3.16 or newer
- OpenMP support
- Internet access during initial GoogleTest dependency setup

The current implementation has been developed and tested using Windows, Visual Studio 2022 (MSVC), and CMake.

### Configure and Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

### Run Tests

```powershell
ctest --test-dir build -C Release --output-on-failure
```

The current test suite contains **18 GoogleTest cases**, including non-square GEMM, block-boundary cases, and comparison against a reference implementation.

### Run Benchmarks

PowerShell example:

```powershell
$env:OMP_DYNAMIC = "FALSE"
$env:OMP_NUM_THREADS = "4"

.\build\Release\matrix_benchmark.exe
```

To compare different thread counts, change `OMP_NUM_THREADS` to `1`, `2`, or `4` and rerun the benchmark.

## Project Structure

```text
cpp-matrix-engine/
├── include/
│   └── matrix.hpp
├── src/
│   ├── main.cpp
│   └── matrix.cpp
├── tests/
│   └── test_matrix.cpp
├── benchmarks/
│   └── benchmark_matrix.cpp
├── CMakeLists.txt
└── README.md
```

## Testing and Correctness

GEMM correctness is validated using GoogleTest, including tests with non-square dimensions and partial edge tiles.

A reference GEMM implementation is used to compare the optimized results within a floating-point tolerance.

Passing tests does not constitute a formal proof of thread safety. Further concurrency analysis and broader testing may be useful.

## Known Limitations

- The matrix data type is currently `float32`.
- The GEMM tile size is fixed at 128.
- Parallelism is partitioned by output row blocks, limiting utilization when the number of row blocks is small.
- AVX2 is enabled through MSVC compiler options and requires compatible target hardware.
- Benchmark results are hardware- and environment-dependent.
- The project is intended for learning and experimentation, not as a replacement for production BLAS libraries.

## Future Extensions

Potential directions for future work include:

- Register blocking and GEMM micro-kernels
- Matrix packing and comparison with optimized BLAS libraries
- Quantized GEMM (INT8 / INT4)
- Tensor operations relevant to neural networks
- Integration with AI inference workloads

These items are future possibilities and are not implemented in the current milestone.

## Development History

Development follows a GitHub workflow using Issues, feature branches, focused commits, correctness tests, performance benchmarks, and Pull Requests.

A completed example is [PR #36 — OpenMP Parallel Blocked GEMM](https://github.com/Allen888510/cpp-matrix-engine/pull/36).

## Project Status

**Milestone 1: CPU GEMM Optimization — Complete**

The current milestone covers foundational C++ matrix operations, cache-aware GEMM, SIMD optimization, OpenMP multithreading, testing, and benchmark methodology.
