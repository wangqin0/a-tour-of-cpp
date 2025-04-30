#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Helper visitor using C++17 features
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    // 1. Basic usage - declare a variant that can hold an int, double, or string
    std::variant<int, double, std::string> v1;
    
    // Initially it holds the first type (int) with default value
    std::cout << "1. Default initialized variant index: " << v1.index() << std::endl;
    std::cout << "   Value: " << std::get<int>(v1) << std::endl;
    
    // 2. Assign different types
    v1 = 42;                // Store an int
    std::cout << "\n2. After storing int:" << std::endl;
    std::cout << "   Index: " << v1.index() << std::endl;
    std::cout << "   Value: " << std::get<int>(v1) << std::endl;
    
    v1 = 3.14;              // Store a double
    std::cout << "\n   After storing double:" << std::endl;
    std::cout << "   Index: " << v1.index() << std::endl;
    std::cout << "   Value: " << std::get<double>(v1) << std::endl;
    
    v1 = std::string("Hello, variant!");  // Store a string
    std::cout << "\n   After storing string:" << std::endl;
    std::cout << "   Index: " << v1.index() << std::endl;
    std::cout << "   Value: " << std::get<std::string>(v1) << std::endl;
    
    // 3. Checking the current type
    std::cout << "\n3. Type checking:" << std::endl;
    if (std::holds_alternative<std::string>(v1)) {
        std::cout << "   v1 currently holds a string" << std::endl;
    }
    
    // 4. Safe access with get_if (returns pointer or nullptr)
    std::cout << "\n4. Safe access with get_if:" << std::endl;
    if (auto str = std::get_if<std::string>(&v1)) {
        std::cout << "   String value: " << *str << std::endl;
    } else {
        std::cout << "   v1 does not hold a string" << std::endl;
    }
    
    // 5. Attempting to access the wrong type
    std::cout << "\n5. Exception handling:" << std::endl;
    try {
        // This will throw because v1 contains a string, not an int
        std::cout << std::get<int>(v1) << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cout << "   Exception caught: " << e.what() << std::endl;
    }
    
    // 6. Using std::visit with a visitor pattern
    std::cout << "\n6. Visitor pattern:" << std::endl;
    
    // Define a visitor using lambda expressions with the helper
    auto visitor = overloaded {
        [](int i) { std::cout << "   Visited int: " << i << std::endl; },
        [](double d) { std::cout << "   Visited double: " << d << std::endl; },
        [](const std::string& s) { std::cout << "   Visited string: " << s << std::endl; }
    };
    
    // Visit multiple variants
    v1 = 100;
    std::visit(visitor, v1);
    
    v1 = 2.718;
    std::visit(visitor, v1);
    
    v1 = std::string("Variant visited!");
    std::visit(visitor, v1);
    
    // 7. Creating a heterogeneous collection
    std::cout << "\n7. Heterogeneous collection:" << std::endl;
    std::vector<std::variant<int, double, std::string>> vec = {
        10,
        std::string("Mixed types"),
        3.1415,
        42,
        std::string("in one container")
    };
    
    std::cout << "   Contents of vector:" << std::endl;
    for (const auto& element : vec) {
        std::visit([](const auto& val) {
            std::cout << "   - " << val << std::endl;
        }, element);
    }
    
    // 8. Variant with user-defined types
    std::cout << "\n8. Variant with custom types:" << std::endl;
    
    struct Point { 
        int x, y;
        void print() const { std::cout << "Point(" << x << ", " << y << ")"; }
    };
    
    struct Circle {
        Point center;
        double radius;
        void print() const { 
            std::cout << "Circle(center: "; 
            center.print(); 
            std::cout << ", radius: " << radius << ")"; 
        }
    };
    
    std::variant<Point, Circle> shape;
    
    shape = Point{10, 20};
    std::visit([](const auto& s) {
        std::cout << "   Shape: ";
        s.print();
        std::cout << std::endl;
    }, shape);
    
    shape = Circle{{5, 5}, 7.5};
    std::visit([](const auto& s) {
        std::cout << "   Shape: ";
        s.print();
        std::cout << std::endl;
    }, shape);
    
    std::cout << "\nEnd of std::variant demonstration" << std::endl;
    return 0;
}