#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <istream>

template<typename T>
class Vector {
public:
    Vector<T>(int);
    Vector<T>(std::initializer_list<T> l) : elem(new T[l.size()]), sz(l.size()) {
        
        for (int i = 0; i < l.size(); ++i) {
            elem[i] = l.begin()[i];
        }
    }
    T* elem;
    int sz;
};

int main()
{
    std::vector v = { 1, 2, 3 };

    std::vector v1 = { 1, 2, 3 };
    std::vector v2 = {"hey", "Hello", "world"};

    std::cout << typeid(v2).name() << std::endl;
    std::cout << typeid(v2[0]).name() << std::endl;

    std::cout << "ok\n";
}