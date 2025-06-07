#include <stdexcept>
#include <iostream>
#include <string>
#include <list>

template<typename T>
class Vector {
private:
	T* elem;
	int sz;
public:
	explicit Vector(int s);
	~Vector() { delete[] elem; }
	
	T& operator[](int i);
	const T& operator[](int i) const;
	int size() const { return sz; }
};

// ===== simple templated member function =====

template<typename T>
Vector<T>::Vector(int s)
{
	if (s < 0) throw std::length_error{"Vector constructor: negative size"};
	elem = new T[s];
	sz = s;
}

template<typename T>
const T& Vector<T>::operator[](int i) const
{
	if (i < 0 || i >= size()) throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}

template<typename T>
T& Vector<T>::operator[](int i)
{
	if (i < 0 || i >= size()) throw std::out_of_range{"Vector::operator[]"};
	return elem[i];
}

// ===== simple begin() and end() =====

template<typename T>
T* begin(Vector<T>& x)
{
	return &x[0];
}

template<typename T>
T* end(Vector<T>& x)
{
	return &x[0] + x.size();
}

template<typename T>
void dump(Vector<T>& x)
{
	for (auto& e : x) std::cout << e << ", ";
	std::cout << "\n";
}

int main() {
	Vector<int> v1(100);
	Vector<std::string> v2(0);
	Vector<std::list<int>> v3(20);
}
