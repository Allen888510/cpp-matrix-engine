cmake_minimum_required(VERSION 3.16)

project(cpp_matrix_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix
    src/matrix.cpp
)

target_include_directories(matrix
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(matrix_engine
    src/main.cpp
)

target_link_libraries(matrix_engine
    PRIVATE
        matrix
)

enable_testing()

add_executable(matrix_tests
    tests/test_matrix.cpp
)

target_link_libraries(matrix_tests
    PRIVATE
        matrix
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(matrix_tests)


include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(matrix_benchmark
    benchmarks/benchmark_matrix.cpp
)

target_link_libraries(matrix_benchmark
    PRIVATE
        matrix
)