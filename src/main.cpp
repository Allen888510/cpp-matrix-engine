#include <iostream>

#include "matrix.hpp"

int main()
{
    Matrix A(2, 3);

    std::cout << "Rows: " << A.rows() << std::endl;
    std::cout << "Cols: " << A.cols() << std::endl;

    A(0, 0) = 1.0f;
    A(0, 1) = 2.0f;
    A(0, 2) = 3.0f;

    A(1, 0) = 4.0f;
    A(1, 1) = 5.0f;
    A(1, 2) = 6.0f;

    std::cout << A(0, 0) << " "
              << A(0, 1) << " "
              << A(0, 2) << std::endl;

    std::cout << A(1, 0) << " "
              << A(1, 1) << " "
              << A(1, 2) << std::endl;

    return 0;
}
