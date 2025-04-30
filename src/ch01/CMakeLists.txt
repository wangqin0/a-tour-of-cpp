# Chapter 1: The Basics

# Example 0: Minimal
add_executable(ch01_minimal minimal.cpp)

# Example 1: Hello World
add_executable(ch01_hello_world hello_world.cpp)

# Example 2: Types, Variables, and Arithmetic 
add_executable(ch01_types_variables types_variables.cpp)

# Example 3: Constants
add_executable(ch01_constants constants.cpp)

# Example 4: Pointers, Arrays, and References
add_executable(ch01_pointers_arrays_references pointers_arrays_references.cpp)

# Link fmt library to all targets
find_package(fmt CONFIG REQUIRED)
target_link_libraries(ch01_hello_world PRIVATE fmt::fmt)
target_link_libraries(ch01_types_variables PRIVATE fmt::fmt)
target_link_libraries(ch01_constants PRIVATE fmt::fmt)
target_link_libraries(ch01_pointers_arrays_references PRIVATE fmt::fmt)
