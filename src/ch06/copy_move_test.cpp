#include <iostream>
#include <vector>
#include <utility>  // for std::move

class Handle {
public:
    Handle() : data(new int(0)), id(counter++) {}

    explicit Handle(int v) : data(new int(v)), id(counter++) {}

    // copy
    Handle(const Handle& other) : data(new int(*other.data)), id(counter++) {}

    Handle& operator=(const Handle& other) {
        // WARN: self-assignment detection
        if (this == &other) { return *this; }

        // *data = *other.data;
        // or delete and copy
        delete data;
        data = new int(*other.data);

        return *this;
    }

    // move
    Handle(Handle&& other) noexcept : data(other.data), id(counter++) {
        other.data = nullptr;
    }

    Handle& operator=(Handle&& other) noexcept {
        // WARN: self-move detection
        if (this == &other) { return *this; }

        // WARN: delete old data before rewrite any pointer
        delete data;
        data = other.data;
        other.data = nullptr;

        return *this;
    }

    ~Handle() {
        delete data;
    }

    int getData() const noexcept {
        return data ? *data : 0;
    }
    
    void setData(int d) {
        if (data) {
            *data = d;
        }
    }

private:
    int* data;
    int id;
    inline static int counter = 0;
};

Handle createHandle(int d) {
    Handle tmp(d);
    return tmp;
}


int main() {
    std::cout << "hello world\n";
}