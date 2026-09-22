#include "matrix.hpp"

#include <stdexcept>
#include<algorithm>

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows),
      cols_(cols),
      data_(rows * cols, 0.0f)
{
}

float& Matrix::operator()(std::size_t row, std::size_t col)
{
    if (row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row * cols_ + col];
}

const float& Matrix::operator()(std::size_t row, std::size_t col) const
{
    if (row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row * cols_ + col];
}

std::size_t Matrix::rows() const
{
    return rows_;
}

std::size_t Matrix::cols() const
{
    return cols_;
}

void Matrix::validate_same_shape(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix dimensions must match");
    }
}

Matrix Matrix::operator+(const Matrix& other) const
{
    validate_same_shape(other);


    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}
    
Matrix Matrix::operator-(const Matrix& other) const
{
    validate_same_shape(other);

    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

Matrix Matrix::operator*(float scalar) const
{
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

Matrix Matrix::transpose() const
{
    Matrix result(cols_, rows_);
    for (std::size_t i = 0; i < rows_; ++i)
    {
        for (std::size_t j = 0; j < cols_; ++j)
        {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (cols_ != other.rows_)
    {
        throw std::invalid_argument(
            "Matrix dimensions are not compatible for multiplication"
        );
    }

    constexpr std::size_t BLOCK_SIZE = 128;

    Matrix result(rows_, other.cols_);

    for (std::size_t ii = 0; ii < rows_; ii += BLOCK_SIZE)
    {
        for (std::size_t kk = 0; kk < cols_; kk += BLOCK_SIZE)
        {
            for (std::size_t jj = 0; jj < other.cols_; jj += BLOCK_SIZE)
            {
                const std::size_t i_end =
                    std::min(ii + BLOCK_SIZE, rows_);

                const std::size_t k_end =
                    std::min(kk + BLOCK_SIZE, cols_);

                const std::size_t j_end =
                    std::min(jj + BLOCK_SIZE, other.cols_);
                
                for (std::size_t i = ii; i < i_end; ++i)
                {
                    for (std::size_t k = kk; k < k_end; ++k)
                    {
                        const float a = data_[i * cols_ + k];
                        const std::size_t result_row = i * other.cols_;
                        const std::size_t other_row = k * other.cols_;

                        float* result_ptr =
                            result.data_.data() + result_row + jj;

                        const float* other_ptr =
                            other.data_.data() + other_row + jj;

                        for (std::size_t j = 0; j < j_end - jj; ++j)
                        {
                            result_ptr[j] += a * other_ptr[j];
                        }
                    }
                } 
            }
        }
    }
    return result;
}
