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

add_test(
    NAME matrix_tests
    COMMAND matrix_tests
)

add_executable(matrix_tests
    tests/test_matrix.cpp
)

target_link_libraries(matrix_tests
    PRIVATE
        matrix
)

