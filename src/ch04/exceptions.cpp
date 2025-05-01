// C++17 Exception Handling Features Demo

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <any>
#include <variant>
#include <optional>
#include <vector>
#include <memory>
#include <filesystem>
#include <fstream>

// Function to demonstrate nested try-catch with C++17 features
void demonstrate_nested_exceptions() {
    std::cout << "\n=== Nested Exception Demonstration ===\n";
    
    try {
        std::cout << "Outer try block\n";
        
        try {
            std::cout << "Inner try block\n";
            throw std::runtime_error("Inner exception occurred");
        } 
        catch (const std::exception& e) {
            std::cout << "Inner catch: " << e.what() << std::endl;
            // C++17 allows us to use nested exception more expressively
            std::throw_with_nested(std::runtime_error("Outer exception occurred"));
        }
    } 
    catch (const std::exception& e) {
        std::cout << "Outer catch: " << e.what() << std::endl;
        
        // C++17 improved exception unwrapping
        try {
            std::rethrow_if_nested(e);
        } 
        catch (const std::exception& nested) {
            std::cout << "Extracted nested exception: " << nested.what() << std::endl;
        }
    }
}

// Demonstration of std::any exception handling (new in C++17)
void demonstrate_any_exceptions() {
    std::cout << "\n=== std::any Exception Handling ===\n";
    
    std::any value;
    
    try {
        // Assign an integer to std::any
        value = 42;
        std::cout << "value contains: " << std::any_cast<int>(value) << std::endl;
        
        // This will throw std::bad_any_cast because the type doesn't match
        std::cout << "Attempting incorrect cast..." << std::endl;
        std::string s = std::any_cast<std::string>(value);
    } 
    catch (const std::bad_any_cast& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "This is a C++17 specific exception from std::any" << std::endl;
    }
}

// Demonstration of std::variant exception handling (new in C++17)
void demonstrate_variant_exceptions() {
    std::cout << "\n=== std::variant Exception Handling ===\n";
    
    std::variant<int, std::string> var = "hello";
    
    try {
        // This will throw std::bad_variant_access
        std::cout << "Attempting to access wrong type..." << std::endl;
        std::cout << std::get<0>(var) << std::endl; 
    } 
    catch (const std::bad_variant_access& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "This is a C++17 specific exception from std::variant" << std::endl;
        
        // Safely get the value using the correct type
        std::cout << "Correct access: " << std::get<std::string>(var) << std::endl;
    }
}

// Demonstration of std::optional exception handling (new in C++17)
void demonstrate_optional_exceptions() {
    std::cout << "\n=== std::optional Exception Handling ===\n";
    
    std::optional<int> opt;  // Empty optional
    
    try {
        // This will throw std::bad_optional_access
        std::cout << "Attempting to access empty optional..." << std::endl;
        std::cout << opt.value() << std::endl;
    } 
    catch (const std::bad_optional_access& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "This is a C++17 specific exception from std::optional" << std::endl;
        
        // Safe way to access optional
        std::cout << "Safe access with value_or(): " << opt.value_or(-1) << std::endl;
    }
    
    // Set a value and try again
    opt = 42;
    std::cout << "After setting value, safe access: " << opt.value() << std::endl;
}

// Demonstration of filesystem exceptions (new in C++17)
void demonstrate_filesystem_exceptions() {
    std::cout << "\n=== std::filesystem Exception Handling ===\n";
    
    try {
        // Attempt to get file size of a non-existent file
        std::cout << "Attempting to access non-existent file..." << std::endl;
        auto size = std::filesystem::file_size("non_existent_file.txt");
    } 
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "Error code: " << e.code() << std::endl;
        std::cout << "Path 1: " << e.path1() << std::endl;
        
        // C++17 filesystem_error provides additional context about the error
        std::cout << "This is a C++17 specific exception from std::filesystem" << std::endl;
    }
}

// Demonstration of uncaught exceptions and std::uncaught_exceptions (improved in C++17)
void demonstrate_uncaught_exceptions() {
    std::cout << "\n=== std::uncaught_exceptions Count ===\n";
    
    struct UncaughtExceptionReporter {
        UncaughtExceptionReporter() {
            std::cout << "Constructor: " << std::uncaught_exceptions() << " uncaught exceptions\n";
        }
        
        ~UncaughtExceptionReporter() {
            std::cout << "Destructor: " << std::uncaught_exceptions() << " uncaught exceptions\n";
        }
    };
    
    try {
        UncaughtExceptionReporter reporter1;
        std::cout << "Before throwing: " << std::uncaught_exceptions() << " uncaught exceptions\n";
        throw std::runtime_error("Test exception");
    } 
    catch (const std::exception& e) {
        UncaughtExceptionReporter reporter2;
        std::cout << "In catch block: " << std::uncaught_exceptions() << " uncaught exceptions\n";
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

// Example of using noexcept (which was improved in C++17)
void demonstrate_noexcept() {
    std::cout << "\n=== noexcept Specifier Demonstration ===\n";
    
    auto func1 = []() noexcept { return "This function promises not to throw"; };
    auto func2 = []() { throw std::runtime_error("This function might throw"); };
    
    std::cout << "func1 is noexcept: " << noexcept(func1()) << std::endl;
    std::cout << "func2 is noexcept: " << noexcept(func2()) << std::endl;
    
    try {
        std::cout << "Calling func1: " << func1() << std::endl;
        
        std::cout << "Calling func2..." << std::endl;
        func2();
    } 
    catch (const std::exception& e) {
        std::cout << "Exception from func2: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "C++17 Exception Handling Demonstration\n";
    std::cout << "======================================\n";
    
    demonstrate_nested_exceptions();
    demonstrate_any_exceptions();
    demonstrate_variant_exceptions();
    demonstrate_optional_exceptions();
    demonstrate_filesystem_exceptions();
    demonstrate_uncaught_exceptions();
    demonstrate_noexcept();
    
    std::cout << "\nAll demonstrations completed successfully.\n";
    
    return 0;
}