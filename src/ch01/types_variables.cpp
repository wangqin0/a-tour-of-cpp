// Chapter 1: Types, Variables, and Arithmetic
#include <fmt/core.h>
#include <cmath>

int main()
{
    // Basic types
    bool is_learning = true;
    char character = 'C';
    int integer = 42;
    double floating_point = 3.14159;
    
    // Output basic type information
    fmt::print("Boolean: {}\n", is_learning);
    fmt::print("Character: {}\n", character);
    fmt::print("Integer: {}\n", integer);
    fmt::print("Double: {}\n", floating_point);
    
    // Arithmetic operations
    int a = 10;
    int b = 3;
    
    fmt::print("\nArithmetic operations:\n");
    fmt::print("a + b = {}\n", a + b);
    fmt::print("a - b = {}\n", a - b);
    fmt::print("a * b = {}\n", a * b);
    fmt::print("a / b = {}\n", a / b);    // Integer division
    fmt::print("a % b = {}\n", a % b);    // Remainder
    
    // Floating point division
    double c = 10.0;
    double d = 3.0;
    fmt::print("c / d = {:.5f}\n", c / d);  // Floating point division with 5 decimal places

    // Type conversions
    fmt::print("\nType conversions:\n");
    int narrowed = floating_point;  // Narrowing conversion
    double widened = integer;       // Widening conversion
    fmt::print("Double to int (narrowing): {}\n", narrowed);
    fmt::print("Int to double (widening): {}\n", widened);
    
    // Using functions from cmath
    fmt::print("\nMath functions:\n");
    fmt::print("sqrt(16) = {}\n", std::sqrt(16));
    fmt::print("pow(2, 3) = {}\n", std::pow(2, 3));
    
    return 0;
} 