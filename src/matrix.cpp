#include "matrix.hpp"

#include <stdexcept>

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

Matrix Matrix::operator+(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result(rows_, cols_);
    for(std::size_t i = 0; i < data_.size(); ++i)
    {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}
    
