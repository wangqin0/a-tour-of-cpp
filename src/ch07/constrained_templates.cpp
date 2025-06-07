#include <thread>
#include <iostream>

template<typename T>
concept Hashable = true;

template<Hashable T>
class Vector
{
private:
    T* elem;
    int sz;
public:
    explicit Vector(int s) : elem(new T[s]), sz(s) {}
};

int main() {
    Vector<int> v1(10);
    std::cout << "ok\n";
}