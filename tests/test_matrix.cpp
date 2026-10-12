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

TEST(MatrixTest, ScalarMultiplication)
{
    Matrix matrix(1, 2);

    matrix(0, 0) = 1.0f;
    matrix(0, 1) = 2.0f;

    Matrix result = matrix * 3.0f;

    EXPECT_FLOAT_EQ(result(0, 0), 3.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 6.0f);

    EXPECT_FLOAT_EQ(matrix(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(matrix(0, 1), 2.0f);
}

TEST(MatrixTest, ScalarMultiplicationNegative)
{
    Matrix matrix(1, 2);

    matrix(0, 0) = 1.0f;
    matrix(0, 1) = -2.0f;

    Matrix result = matrix * -2.0f;

    EXPECT_FLOAT_EQ(result(0, 0), -2.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 4.0f);
}

TEST(MatrixTest, ScalarMultiplicationByZero)
{
    Matrix matrix(1, 2);

    matrix(0, 0) = 5.0f;
    matrix(0, 1) = -3.0f;

    Matrix result = matrix * 0.0f;

    EXPECT_FLOAT_EQ(result(0, 0), 0.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 0.0f);
}

TEST(MatrixTest, TransposeRectangular)
{
    Matrix matrix(2, 3);

    matrix(0, 0) = 1.0f;
    matrix(0, 1) = 2.0f;
    matrix(0, 2) = 3.0f;

    matrix(1, 0) = 4.0f;
    matrix(1, 1) = 5.0f;
    matrix(1, 2) = 6.0f;

    Matrix result = matrix.transpose();

    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_FLOAT_EQ(result(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 4.0f);

    EXPECT_FLOAT_EQ(result(1, 0), 2.0f);
    EXPECT_FLOAT_EQ(result(1, 1), 5.0f);

    EXPECT_FLOAT_EQ(result(2, 0), 3.0f);
    EXPECT_FLOAT_EQ(result(2, 1), 6.0f);
}

TEST(MatrixTest, TransposeSquare)
{
    Matrix matrix(2, 2);

    matrix(0, 0) = 1.0f;
    matrix(0, 1) = 2.0f;
    matrix(1, 0) = 3.0f;
    matrix(1, 1) = 4.0f;

    Matrix result = matrix.transpose();

    EXPECT_FLOAT_EQ(result(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 3.0f);
    EXPECT_FLOAT_EQ(result(1, 0), 2.0f);
    EXPECT_FLOAT_EQ(result(1, 1), 4.0f);
}

TEST(MatrixTest, DoubleTransposeReturnsOriginal)
{
    Matrix matrix(2, 3);

    matrix(0, 0) = 1.0f;
    matrix(0, 1) = 2.0f;
    matrix(0, 2) = 3.0f;

    matrix(1, 0) = 4.0f;
    matrix(1, 1) = 5.0f;
    matrix(1, 2) = 6.0f;

    Matrix result = matrix.transpose().transpose();

    EXPECT_EQ(result.rows(), matrix.rows());
    EXPECT_EQ(result.cols(), matrix.cols());

    for (std::size_t row = 0; row < matrix.rows(); ++row)
    {
        for (std::size_t col = 0; col < matrix.cols(); ++col)
        {
            EXPECT_FLOAT_EQ(result(row, col), matrix(row, col));
        }
    }
}

TEST(MatrixTest, MatrixMultiplication)
{
    Matrix A(2, 3);
    Matrix B(3, 2);

    A(0, 0) = 1.0f;
    A(0, 1) = 2.0f;
    A(0, 2) = 3.0f;
    A(1, 0) = 4.0f;
    A(1, 1) = 5.0f;
    A(1, 2) = 6.0f;

    B(0, 0) = 7.0f;
    B(0, 1) = 8.0f;
    B(1, 0) = 9.0f;
    B(1, 1) = 10.0f;
    B(2, 0) = 11.0f;
    B(2, 1) = 12.0f;

    Matrix result = A * B;

    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_FLOAT_EQ(result(0, 0), 58.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 64.0f);
    EXPECT_FLOAT_EQ(result(1, 0), 139.0f);
    EXPECT_FLOAT_EQ(result(1, 1), 154.0f);
}

TEST(MatrixTest, MatrixMultiplicationDimensionMismatch)
{
    Matrix A(2, 3);
    Matrix B(2, 2);

    EXPECT_THROW(
        A * B,
        std::invalid_argument
    );
}

TEST(MatrixTest, MatrixMultiplicationByIdentity)
{
    Matrix A(2, 2);

    A(0, 0) = 1.0f;
    A(0, 1) = 2.0f;
    A(1, 0) = 3.0f;
    A(1, 1) = 4.0f;

    Matrix I(2, 2);

    I(0, 0) = 1.0f;
    I(1, 1) = 1.0f;

    Matrix result = A * I;

    EXPECT_FLOAT_EQ(result(0, 0), 1.0f);
    EXPECT_FLOAT_EQ(result(0, 1), 2.0f);
    EXPECT_FLOAT_EQ(result(1, 0), 3.0f);
    EXPECT_FLOAT_EQ(result(1, 1), 4.0f);
}


TEST(MatrixTest, OpenMPBlockedGEMMNonSquare)
{
    const std::size_t M = 300;
    const std::size_t K = 137;
    const std::size_t N = 259;

    Matrix A(M, K);
    Matrix B(K, N);

    for (std::size_t i = 0; i < M; ++i)
    {
        for (std::size_t k = 0; k < K; ++k)
        {
            A(i, k) = 1.0f;
        }
    }

    for (std::size_t k = 0; k < K; ++k)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            B(k, j) = 2.0f;
        }
    }

    Matrix C = A * B;

    ASSERT_EQ(C.rows(), M);
    ASSERT_EQ(C.cols(), N);

    for (std::size_t i = 0; i < M; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            EXPECT_FLOAT_EQ(C(i, j), 274.0f);
        }
    }
}


TEST(MatrixTest, OpenMPBlockedGEMMAgainstReference)
{
    constexpr std::size_t M = 257;
    constexpr std::size_t K = 131;
    constexpr std::size_t N = 135;

    Matrix A(M, K);
    Matrix B(K, N);

    for (std::size_t i = 0; i < M; ++i)
    {
        for (std::size_t k = 0; k < K; ++k)
        {
            A(i, k) = static_cast<float>(
                static_cast<int>((i + 3 * k) % 17) - 8
            ) * 0.25f;
        }
    }

    for (std::size_t k = 0; k < K; ++k)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            B(k, j) = static_cast<float>(
                static_cast<int>((2 * k + j) % 19) - 9
            ) * 0.125f;
        }
    }

    Matrix expected(M, N);

    // Reference GEMM: 簡單、容易驗證的 i-j-k 寫法
    for (std::size_t i = 0; i < M; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            float sum = 0.0f;

            for (std::size_t k = 0; k < K; ++k)
            {
                sum += A(i, k) * B(k, j);
            }

            expected(i, j) = sum;
        }
    }

    // 你實際優化過的 OpenMP + Blocked GEMM
    Matrix actual = A * B;

    ASSERT_EQ(actual.rows(), M);
    ASSERT_EQ(actual.cols(), N);

    for (std::size_t i = 0; i < M; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            EXPECT_NEAR(actual(i, j), expected(i, j), 1e-3f)
                << "Mismatch at (" << i << ", " << j << ")";
        }
    }
}
