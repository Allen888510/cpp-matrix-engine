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

    Matrix result(rows_, other.cols_);

    for (std::size_t i = 0; i < rows_; ++i)
    {
        for (std::size_t k = 0; k < cols_; ++k)
        {
            const float a = data_[i * cols_ + k];

            for (std::size_t j = 0; j < other.cols_; ++j)
            {
                result.data_[i * other.cols_ + j] +=
                    a * other.data_[k * other.cols_ + j];
            }
        }
    }
    return result;
}
