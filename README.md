# A Tour of C++ (3rd Edition) - Notes and Examples

This project contains examples and notes based on Bjarne Stroustrup's "A Tour of C++, 3rd Edition" book. It's organized by chapters, with each chapter containing example code that demonstrates the concepts discussed in the book.

## Project Structure

```
a-tour-of-cpp/
├── CMakeLists.txt       # Main CMake configuration
├── CMakePresets.json    # CMake presets configuration
├── vcpkg.json           # vcpkg manifest file
├── setup-env.bat        # Windows environment setup script
├── setup-env.sh         # Unix/Linux/macOS environment setup script
├── include/             # Header files
├── src/                 # Source files, organized by chapter
│   └── chapter01/       # Chapter 1: The Basics
│       ├── hello_world.cpp
│       ├── types_variables.cpp
│       ├── constants.cpp
│       ├── pointers_arrays_references.cpp
│       └── llvm_basic.cpp
└── test/                # Test files
```

## Prerequisites

- CMake 3.20 or higher
- Clang compiler (automatically selected in CMakeLists.txt)
- vcpkg (for package management)

## Dependencies

Currently this project depends on:
- fmt: Modern formatting library for C++

## Setup

1. Clone this repository:
   ```bash
   git clone https://github.com/wangqin0/a-tour-of-cpp.git
   cd a-tour-of-cpp
   ```

2. Set up vcpkg:
   ```bash
   # If you don't have vcpkg installed:
   git clone https://github.com/microsoft/vcpkg.git
   ./vcpkg/bootstrap-vcpkg.sh  # On Unix-like systems
   ./vcpkg/bootstrap-vcpkg.bat  # On Windows
   ```

## Setting Environment Variables

### Using Convenience Scripts

The project includes scripts to automatically set up environment variables:

**Windows:**
```bash
# Run the setup script (optionally providing vcpkg path)
setup-env.bat C:\path\to\vcpkg
```

**Unix/Linux/macOS:**
```bash
# Make the script executable
chmod +x setup-env.sh

# Run the script (optionally providing vcpkg path)
source ./setup-env.sh /path/to/vcpkg
```

### Manual Environment Variable Setup

1. **VCPKG_ROOT**:
   Path to vcpkg installation

   **Windows:**
   ```bash
   set VCPKG_ROOT=C:\path\to\vcpkg
   ```

   **Unix/macOS/Linux:**
   ```bash
   export VCPKG_ROOT=/path/to/vcpkg
   ```

### Setting Variables Permanently

#### Windows
1. Open Start menu and search for "Environment Variables"
2. Click "Edit the system environment variables"
3. In the System Properties window, click "Environment Variables"
4. Add or modify the variables in the User variables section
5. Click OK to save

#### macOS/Linux
Add to your `~/.bashrc`, `~/.zshrc`, or appropriate shell configuration file:
```bash
export VCPKG_ROOT=/path/to/vcpkg
```

## Building with CMake Presets

This project uses CMake Presets to simplify the build process. The `CMakePresets.json` file defines standardized build configurations.

### Building the Project

```bash
# Configure and build using CMake presets
cmake --preset=default
cmake --build --preset=default
```

When you run these commands:
1. CMake processes your vcpkg.json file
2. vcpkg automatically downloads and builds the dependencies
3. The packages are installed to the build directory
4. CMake finds and uses these packages

### Using Visual Studio Code

1. Install the CMake Tools extension
2. Open the project folder in VS Code
3. The extension will automatically detect and use the CMake presets

## Running the Examples

After building, you can run any of the examples. From the build directory:

```bash
# Run the Hello World example
./src/chapter01/ch01_hello_world

# Run the Types and Variables example
./src/chapter01/ch01_types_variables

# Run the Constants example
./src/chapter01/ch01_constants

# Run the Pointers, Arrays, and References example
./src/chapter01/ch01_pointers_arrays_references

# Run the LLVM Basic example
./src/chapter01/ch01_llvm_basic
```

## Managing Dependencies with vcpkg.json

The `vcpkg.json` file specifies your project's dependencies:

```json
{
  "dependencies": [
    "fmt"
  ]
}
```

To add a new dependency, simply add its name to the "dependencies" array.

## Adding More Chapters

As you progress through the book, you can add more chapters by:

1. Creating a new directory under `src/` (e.g., `src/chapter02/`)
2. Adding example code files
3. Creating a `CMakeLists.txt` file in the new chapter directory
4. Adding the new chapter directory to the main `CMakeLists.txt` using `add_subdirectory()`

## License

This project is licensed under the MIT License - see the LICENSE file for details. 