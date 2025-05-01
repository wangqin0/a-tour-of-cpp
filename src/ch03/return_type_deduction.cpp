#include <iostream>
#include <format>

auto add(int a, int b) -> int {
    return a + b;
}

auto main() -> int {
    auto result = add(3, 4);
    std::cout << std::format("Result: {}\n", result);
    return 0;
}
