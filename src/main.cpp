#include <iostream>
#include <stdexcept>

#include "matrix.hpp"

int main()
{
    Matrix A(2, 3);

    A(0, 0) = 1.0f;
    A(0, 1) = 2.0f;
    A(0, 2) = 3.0f;

    A(1, 0) = 4.0f;
    A(1, 1) = 5.0f;
    A(1, 2) = 6.0f;


    Matrix B(2, 3);
    B(0, 0) = 7.0f;
    B(0, 1) = 1.0f;
    B(0, 2) = 9.0f;

    B(1, 0) = 10.0f;
    B(1, 1) = 11.0f;
    B(1, 2) = 3.0f;

    Matrix C(3, 2); 
    C(0, 0) = 1.0f;
    C(0, 1) = 2.0f;
    C(1, 0) = 3.0f;
    C(1, 1) = 4.0f;
    C(2, 0) = 5.0f;
    C(2, 1) = 6.0f;
    

    Matrix D = B - A;

    std::cout << "Result of B - A:" << std::endl;
    for (std::size_t i = 0; i < D.rows(); ++i)
    {
       for (std::size_t j = 0; j < D.cols(); ++j)
        {
            std::cout << D(i, j) << " ";
        }
        std::cout << std::endl;
    }

    try
    {
        Matrix E = A - C;

        std::cout << "Result of A - C:" << std::endl;
        for (std::size_t i = 0; i < E.rows(); ++i)
        {
            for (std::size_t j = 0; j < E.cols(); ++j)
            {
                std::cout << E(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Caught error: " << e.what() << std::endl;
    }
}

