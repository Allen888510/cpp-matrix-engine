#include <iostream>
#include <string>
#include <stdexcept>

#include "matrix.hpp"

int passed = 0;
int failed = 0;

void expect_true(bool condition, const std::string& test_name)
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

void test_dimensions()
{
    Matrix A(2, 3);
    expect_true(
        A.rows() == 2 && A.cols() == 3,
        "Matrix dimensions"
    );
}

void test_element_access()
{
    Matrix B(2, 2);
    B(1, 1) = 2.0f;

    expect_true(
        B(1, 1) == 2.0f,
        "Element access"
    );
}

void test_addition()
{
    Matrix C(1, 2);
    Matrix D(1, 2);

    C(0, 0) = 1.0f;
    C(0, 1) = 2.0f;

    D(0, 0) = 3.0f;
    D(0, 1) = 4.0f;

    Matrix E = C + D;

    expect_true(
        E(0, 0) == 4.0f && E(0, 1) == 6.0f,
        "Matrix addition"
    );
}

void test_subtraction()
{
    Matrix C(1, 2);
    Matrix D(1, 2);

    C(0, 0) = 1.0f;
    C(0, 1) = 2.0f;

    D(0, 0) = 3.0f;
    D(0, 1) = 4.0f;

    Matrix J = C - D;

    expect_true(
        J(0, 0) == -2.0f && J(0, 1) == -2.0f,
        "Matrix subtraction"
    );
}

void test_addition_dimension_mismatch()
{
    bool threw_invalid_argument = false;

    try
    {
        Matrix F(2, 3);
        Matrix G(3, 2);

        Matrix H = F + G;
    }
    catch (const std::invalid_argument&)
    {
        threw_invalid_argument = true;
    }

    expect_true(
        threw_invalid_argument,
        "Addition dimension mismatch"
    );
}

void test_out_of_range_access()
{
    bool threw_out_of_range = false;

    try
    {
        Matrix I(2, 2);

        float x = I(10, 10);
    }
    catch (const std::out_of_range&)
    {
        threw_out_of_range = true;
    }

    expect_true(
        threw_out_of_range,
        "Out-of-range access"
    );
}

int main()
{
    test_dimensions();
    test_element_access();
    test_addition();
    test_subtraction();
    test_addition_dimension_mismatch();
    test_out_of_range_access();

    std::cout << std::endl;
    std::cout << passed << " passed, "
              << failed << " failed"
              << std::endl;

    return failed == 0 ? 0 : 1; //0 → success, non-zero → failure
}
