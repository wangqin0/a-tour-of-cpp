// Chapter 1: Pointers, Arrays, and References
#include <fmt/core.h>
#include <array>
#include <vector>

// Function taking a reference parameter
void increment_by_reference(int& value)
{
    value += 1;
}

// Function taking a pointer parameter
void increment_by_pointer(int* ptr)
{
    (*ptr) += 1;
}

int main()
{
    //
    // ARRAYS
    //
    fmt::print("Arrays:\n");
    
    // C-style array
    int c_array[5] = {1, 2, 3, 4, 5};
    fmt::print("C-style array elements: ");
    for (int i = 0; i < 5; ++i) {
        fmt::print("{} ", c_array[i]);
    }
    fmt::print("\n");
    
    // std::array (fixed size, from STL)
    std::array<int, 5> std_array = {10, 20, 30, 40, 50};
    fmt::print("std::array elements: ");
    for (const auto& element : std_array) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");
    
    // std::vector (dynamic size, from STL)
    std::vector<int> vec = {100, 200, 300};
    fmt::print("std::vector elements: ");
    for (const auto& element : vec) {
        fmt::print("{} ", element);
    }
    fmt::print("\n\n");
    
    //
    // POINTERS
    //
    fmt::print("Pointers:\n");
    
    // Basic pointer
    int value = 42;
    int* ptr = &value;  // Address-of operator
    
    fmt::print("value = {}\n", value);
    fmt::print("&value = {:p}\n", static_cast<void*>(&value));  // Address of value
    fmt::print("ptr = {:p}\n", static_cast<void*>(ptr));        // Pointer content (an address)
    fmt::print("*ptr = {}\n", *ptr);  // Dereferenced pointer value
    
    // Modifying via pointer
    *ptr = 99;
    fmt::print("After *ptr = 99, value = {}\n", value);
    
    // Null pointer
    int* null_ptr = nullptr;
    fmt::print("null_ptr = {:p}\n\n", static_cast<void*>(null_ptr));
    
    //
    // REFERENCES
    //
    fmt::print("References:\n");
    
    int original = 10;
    int& ref = original;  // Reference to original
    
    fmt::print("original = {}\n", original);
    fmt::print("ref = {}\n", ref);
    
    // Modifying via reference
    ref = 20;
    fmt::print("After ref = 20, original = {}\n\n", original);
    
    //
    // Using with functions
    //
    fmt::print("Function calls:\n");
    
    int x = 5;
    fmt::print("Initial x = {}\n", x);
    
    increment_by_reference(x);
    fmt::print("After increment_by_reference: x = {}\n", x);
    
    increment_by_pointer(&x);
    fmt::print("After increment_by_pointer: x = {}\n", x);
    
    return 0;
} 