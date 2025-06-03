// copy_move_demo.cpp
// Demonstrates C++ copy and move semantics with detailed logging and comments. Renamed class to "Handle" to reflect resource handling.

#include <iostream>
#include <vector>
#include <utility> // For std::move

// A simple class that manages a dynamic resource and logs copy/move operations.
class Handle {
private:
    int* data_;       // Pointer to a dynamic integer, simulating a resource
    int id_;          // Unique ID for each instance (for logging)
    static int counter_; // Static counter to assign unique IDs

public:
    // Default constructor
    Handle() : data_(new int(0)), id_(++counter_) {
        std::cout << "[Default Constructor]   " << "Handle#" << id_ << " created, data_ = " << *data_ << " at " << data_ << "\n";
    }

    // Parameterized constructor
    Handle(int value) : data_(new int(value)), id_(++counter_) {
        std::cout << "[Param Constructor]     " << "Handle#" << id_ << " created with value " << *data_ << " at " << data_ << "\n";
    }

    // Copy constructor
    Handle(const Handle& other) : data_(new int(*other.data_)), id_(++counter_) {
        std::cout << "[Copy Constructor]      " << "Handle#" << id_
                  << " copied from Handle#" << other.id_
                  << ", data_ = " << *data_ << " at " << data_ << "\n";
    }

    // Copy assignment operator
    Handle& operator=(const Handle& other) {
        if (this == &other) {
            std::cout << "[Copy Assignment]       " << "Self-assignment detected for Handle#" << id_ << "\n";
            return *this;
        }
        delete data_;                                  // Clean up existing resource
        data_ = new int(*other.data_);                 // Allocate new resource and copy
        std::cout << "[Copy Assignment]       " << "Handle#" << id_
                  << " assigned from Handle#" << other.id_
                  << ", data_ = " << *data_ << " at " << data_ << "\n";
        return *this;
    }

    // Move constructor
    Handle(Handle&& other) noexcept : data_(other.data_), id_(++counter_) {
        other.data_ = nullptr; // Take ownership, leave other in a valid but empty state
        std::cout << "[Move Constructor]      " << "Handle#" << id_
                  << " moved from Handle#" << other.id_
                  << ", data_ = " << *data_ << " at " << data_ << "\n";
    }

    // Move assignment operator
    Handle& operator=(Handle&& other) noexcept {
        if (this == &other) {
            std::cout << "[Move Assignment]       " << "Self-move detected for Handle#" << id_ << "\n";
            return *this;
        }
        delete data_;           // Free existing resource
        data_ = other.data_;    // Transfer ownership
        other.data_ = nullptr;  // Leave other in a valid state
        std::cout << "[Move Assignment]       " << "Handle#" << id_
                  << " moved-assign from Handle#" << other.id_
                  << ", data_ at " << data_ << "\n";
        return *this;
    }

    // Destructor
    ~Handle() {
        if (data_) {
            std::cout << "[Destructor]           " << "Handle#" << id_ << " destroyed, deleting data_ at " << data_ << "\n";
        } else {
            std::cout << "[Destructor]           " << "Handle#" << id_ << " destroyed, no data to delete (moved-from)\n";
        }
        delete data_;
    }

    // Accessor
    int getValue() const { return (data_ ? *data_ : 0); }

    // Mutator
    void setValue(int value) {
        if (data_) {
            *data_ = value;
        }
    }
};

// Initialize static counter_
int Handle::counter_ = 0;

// A function that returns a Handle object by value
Handle createHandle(int value) {
    Handle temp(value);
    std::cout << "[createHandle]             Returning Handle#" << temp.getValue() << " by value\n";
    return temp; // Should invoke move constructor in C++11+ (RVO or move)
}

int main() {
    std::cout << "--- 1. Default Construction ---\n";
    Handle h1;                 // Default constructor

    std::cout << "\n--- 2. Parameterized Construction ---\n";
    Handle h2(42);             // Param constructor

    std::cout << "\n--- 3. Copy Construction ---\n";
    Handle h3 = h2;            // Copy constructor

    std::cout << "\n--- 4. Copy Assignment ---\n";
    h1 = h2;                 // Copy assignment

    std::cout << "\n--- 5. Move Construction with std::move ---\n";
    Handle h4 = std::move(h2); // Move constructor

    std::cout << "\n--- 6. Move Assignment with std::move ---\n";
    h3 = std::move(h4);      // Move assignment

    std::cout << "\n--- 7. Returning by Value (createHandle) ---\n";
    Handle h5 = createHandle(99); // createHandle returns by value

    std::cout << "\n--- 8. Move Semantics in std::vector ---\n";
    std::vector<Handle> vec;
    vec.reserve(3);
    vec.push_back(Handle(7)); // Temporary Handle(7) is moved into the vector
    vec.push_back(Handle(8));
    vec.push_back(Handle(9));

    std::cout << "\n--- 9. std::move on a local object inserted to vector ---\n";
    Handle local(100);
    vec.push_back(std::move(local)); // Move local into vector

    std::cout << "\n--- End of main: Destruction begins ---\n";
    return 0;
}

/*
Guide and Insights (for reference after you write your own version):

1. Class Definition (Handle):
   - Manage a dynamic resource (e.g., int* data_).
   - Include a unique ID (id_) and a static counter to track instances.
   - Implement:
     a. Default constructor: allocate resource and log.
     b. Parameterized constructor: allocate resource with given value and log.
     c. Copy constructor: deep copy resource, assign new ID, and log.
     d. Copy assignment operator: check self-assignment, delete existing resource, deep copy, and log.
     e. Move constructor: take ownership of the pointer, null out source, assign new ID, and log.
     f. Move assignment operator: check self-move, delete existing resource, transfer ownership, null out source, and log.
     g. Destructor: delete resource if not null, and log.
   - Include accessors (getValue) and mutators (setValue) as needed.

2. createHandle Function:
   - Create a local Handle with a specific value.
   - Log a message before returning.
   - Return by value to trigger move semantics or rely on RVO.

3. main Function:
   - Demonstrate each constructor and assignment:
     1) Default construction (Handle h1;).
     2) Parameterized construction (Handle h2(42);).
     3) Copy construction (Handle h3 = h2;).
     4) Copy assignment (h1 = h2;).
     5) Move construction (Handle h4 = std::move(h2);).
     6) Move assignment (h3 = std::move(h4);).
     7) Returning by value (Handle h5 = createHandle(99);).
   - Show move semantics with std::vector:
     - Reserve capacity to avoid reallocations.
     - push_back temporaries (Handle(7), etc.) to invoke move constructor.
     - std::move a local object into the vector.

4. Logging:
   - Prefix logs with operation type (e.g., "[Copy Constructor]").
   - Identify instances by Handle#<id_> and show resource pointer and value.
   - In move operations, show that the source’s data_ becomes nullptr.
   - In destructor, differentiate between destroyed objects with or without data.

5. Testing and Compilation:
   - Compile with C++17 or later: g++ -std=c++17 copy_move_demo.cpp -o demo
   - Run: ./demo and observe console output to verify correct calls and resource states.
   - Compare your implementation step-by-step with the detailed guide above.
*/
