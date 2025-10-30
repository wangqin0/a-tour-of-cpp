#include <iostream>

using namespace std;

// variable templates
template<typename T>
constexpr T viscosity = 0.4;

// aliases
template<typename T>
class Vector {
public:
    using valueType = T;
};

template<typename C>
using ValueType = C::ValueType;

template<typename Container>
void algo(Container& C)
{
    Vector<ValueType<Container>> vec;
}

// compile-time if
template<typename T>
void update(T& target)
{
    if constexpr(sizeof(T) == sizeof(int))
    {
        cout << "update int\n";
    }
    else
    {
        cout << "update non-int\n";
    }
}


int main()
{
    // variable templates
    auto vis2 = 2 * viscosity<double>;


    // compile-time if
    int i = 9;
    update(i);
    cout << "ok" << endl;
}
