// Chapter 1: Constants
#include <fmt/core.h>

// Global constant (old C-style)
#define PI_MACRO 3.14159265359

// Global constant (C++ style)
constexpr double PI = 3.14159265359;

// Enum constants
enum Color { RED, GREEN, BLUE };

// Enum class (scoped enum)
enum class TrafficLight { RED, YELLOW, GREEN };

int main()
{
    // Literal constants
    fmt::print("Literal constants:\n");
    fmt::print("Integer: {}\n", 42);
    fmt::print("Float: {}\n", 3.14);
    fmt::print("Character: {}\n", 'A');
    fmt::print("String: {}\n", "Hello");
    fmt::print("Boolean: {}\n", true);
    
    // const keyword
    const int days_in_week = 7;
    fmt::print("\nConstant variable: days_in_week = {}\n", days_in_week);
    
    // Cannot modify a const
    // days_in_week = 8;  // This would cause a compile error
    
    // constexpr - compile-time constants
    constexpr int square_of_7 = 7 * 7;
    fmt::print("Compile-time constant: square_of_7 = {}\n", square_of_7);
    
    // Using #define constants (not recommended in modern C++)
    fmt::print("\nMacro-defined constant: PI_MACRO = {}\n", PI_MACRO);
    
    // Using constexpr (recommended)
    fmt::print("constexpr constant: PI = {}\n", PI);
    
    // Enum constants
    Color color = GREEN;
    fmt::print("\nEnum constant (plain enum): color = {}\n", static_cast<int>(color));
    
    // Enum class constants (type-safe)
    TrafficLight light = TrafficLight::RED;
    fmt::print("Enum class constant: TrafficLight::RED = {}\n", static_cast<int>(light));
    
    return 0;
} 