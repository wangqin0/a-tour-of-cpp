cmake_minimum_required(VERSION 3.20)

# Set compiler to Clang if CC/CXX environment variables are not set
if(NOT DEFINED ENV{CC})
  set(CMAKE_C_COMPILER clang)
endif()
if(NOT DEFINED ENV{CXX})
  set(CMAKE_CXX_COMPILER clang++)
endif()

project(ATourOfCpp
    VERSION 0.1.0
    DESCRIPTION "Notes and exercises for A Tour of C++, 3rd edition"
    LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(include)

find_package(fmt CONFIG REQUIRED)

# Add chapters as subdirectories
add_subdirectory(src/ch01)
add_subdirectory(src/ch02)
add_subdirectory(src/ch03)
add_subdirectory(src/ch04)
