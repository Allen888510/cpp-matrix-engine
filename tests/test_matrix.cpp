#include <stdexcept>

#include <gtest/gtest.h>

#include "matrix.hpp"

int passed = 0;
int failed = 0;

void expect_true(bool condition, const char* test_name)
{
    if (condition)
    {
        ++passed;
        std::cout << "[PASS] " << test_name << std::endl;
    }
    else
    {
        ++failed;
        std::cout << "[FAIL] " << test_name << std::endl;
    }
}

TEST(MatrixTest, Dimensions)
{
    Matrix matrix(2, 3);

    EXPECT_EQ(matrix.rows(), 2);
    EXPECT_EQ(matrix.cols(), 3);
}

TEST(MatrixTest, ElementAccess)
{
    Matrix matrix(2, 2);

    matrix(1, 1) = 2.0f;

    EXPECT_FLOAT_EQ(matrix(1, 1), 2.0f);
}

TEST(MatrixTest, Addition)
{
    Matrix left(1, 2);
    Matrix right(1, 2);

    left(0, 0) = 1.0f;
    left(0, 1) = 2.0f;

    right(0, 0) = 3.0f;
    right(0, 1) = 4.0f;

    Matrix result = left + right;

    EXPECT_FLOAT_EQ(result(0, 0), 4.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 6.0f);
}

TEST(MatrixTest, Subtraction)
{
    Matrix left(1, 2);
    Matrix right(1, 2);

    left(0, 0) = 1.0f;
    left(0, 1) = 2.0f;

    right(0, 0) = 3.0f;
    right(0, 1) = 4.0f;

    Matrix result = left - right;

    EXPECT_FLOAT_EQ(result(0, 0), -2.0f);
    EXPECT_FLOAT_EQ(result(0, 1), -2.0f);
}

TEST(MatrixTest, AdditionDimensionMismatch)
{
    Matrix left(2, 3);
    Matrix right(3, 2);

    EXPECT_THROW(
        left + right,
        std::invalid_argument
    );
}

TEST(MatrixTest, SubtractionDimensionMismatch)
{
    Matrix left(2, 3);
    Matrix right(3, 2);

    EXPECT_THROW(
        left - right,
        std::invalid_argument
    );
}

TEST(MatrixTest, OutOfRangeAccess)
{
    Matrix matrix(2, 2);

    EXPECT_THROW(
        matrix(10, 10),
        std::out_of_range
    );
}
