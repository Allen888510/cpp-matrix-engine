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
    if(row >= rows_ || col >= cols_)
    {
        throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row * cols_ + col];
}

const float& Matrix::operator()(std::size_t row, std::size_t col) const
{
    if(row >= rows_ || col >= cols_)
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
